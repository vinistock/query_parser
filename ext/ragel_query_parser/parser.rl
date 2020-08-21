/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"

static VALUE rb_mEncoding;
static VALUE utf_8;
static VALUE rb_cParams;

%%{
    machine parser;

    action start_word {
        encoded = 0;
        buffer = p;
    }

    action set_encoded {
        encoded = 1;
    }

    action raise_argument_error {
        rb_raise(rb_eArgError, "invalid encoding");
    }

    action parameter_key {
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_str_intern(rb_obj_freeze(current_key));
    }

    action regular_parameter_value {
        current_value = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_value = rb_funcall(unescaper, rb_intern("call"), 1, current_value);

        rb_hash_aset(parameters, current_key, current_value);
    }

    action array_parameter_value {
        current_value = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_value = rb_funcall(unescaper, rb_intern("call"), 1, current_value);

        rb_hash_aset(parameters, current_key, rb_str_split(current_value, ","));
    }

    parameter_separator = [&;];
    encoded_content = ("+" | "%" xdigit xdigit) >set_encoded;
    invalid_encoded_content = ("%" ^digit ^digit?) %raise_argument_error;
    parameter_content = (alnum | [\-._~:/#@!$'()*,] | encoded_content)+ >start_word;
    regular_parameter = parameter_content %parameter_key "=" parameter_content %regular_parameter_value;
    array_parameter = parameter_content %parameter_key "[]=" parameter_content %array_parameter_value;
    parameter = array_parameter | regular_parameter;

    main := (any* invalid_encoded_content any*) | (parameter (parameter_separator parameter)*);
}%%

%% write data;

/*
    parser = RagelQueryParser.new
    parser.parse(query, separator = "&", unescaper = -> {})
*/
static VALUE parse(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator, unescaper;
    rb_scan_args(argc, argv, "11&", &query_string, &separator, &unescaper);
    // TODO: use separator

    rb_encoding *encoding = rb_enc_get(query_string);
    const char *p = RSTRING_PTR(query_string);
    const char *pe = p + RSTRING_LEN(query_string);
    const char *eof = pe;
    const char *buffer;
    int cs = 0, encoded = 0;
    VALUE current_key = Qnil, current_value = Qnil, parameters = rb_hash_new();

    if (NIL_P(unescaper)) {
        unescaper = rb_funcall(rb_obj_class(self), rb_intern("method"), 1, ID2SYM(rb_intern("unescape")));
    }

    %%{
        write init;
        write exec;
    }%%

    return parameters;
}

static VALUE parser_initialize(VALUE self, VALUE params_class, VALUE key_space_limit, VALUE param_depth_limit) {
    rb_iv_set(self, "@params_class", params_class);
    rb_iv_set(self, "@key_space_limit", key_space_limit);
    rb_iv_set(self, "@param_depth_limit", param_depth_limit);
    return self;
}

static char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

static VALUE unescape(VALUE self, VALUE string) {
    char *str = RSTRING_PTR(string);
    char *pstr = str, *buf = malloc(strlen(str) + 1), *pbuf = buf;
    VALUE decoded_url;

    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                pstr += 2;
            }
        } else if (*pstr == '+') {
            *pbuf++ = ' ';
        } else {
            *pbuf++ = *pstr;
        }

        pstr++;
    }

    *pbuf = '\0';
    decoded_url = rb_str_new_cstr(buf);
    free(buf);
    return rb_funcall(decoded_url, rb_intern("force_encoding"), 1, utf_8);
}

static VALUE make_default(VALUE self, VALUE key_space_limit, VALUE param_depth_limit) {
    return rb_funcall(self, rb_intern("new"), 3, rb_cParams, key_space_limit, param_depth_limit);
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    rb_cParams = rb_const_get(rb_mRagelQueryParser, rb_intern("Params"));
    rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));

    rb_funcall(rb_cParser, rb_intern("attr_reader"), 2, ID2SYM(rb_intern("key_space_limit")), ID2SYM(rb_intern("param_depth_limit")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 3);
    rb_define_method(rb_cParser, "parse_query", parse, -1);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
    rb_define_singleton_method(rb_cParser, "make_default", make_default, 2);
}
