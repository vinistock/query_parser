/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"
#include "params.h"

static VALUE rb_mEncoding;
static VALUE utf_8;
static VALUE rb_cParams;
static VALUE rb_eParameterTypeError;

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

        current_key = rb_obj_freeze(current_key);
    }

    action regular_parameter_value {
        current_value = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_value = rb_funcall(unescaper, rb_intern("call"), 1, current_value);

        temp_value = params_access(parameters, current_key);

        if (RTEST(temp_value)) {
            if (RTEST(rb_obj_is_kind_of(temp_value, rb_cArray))) {
                params_set(parameters, current_key, rb_ary_push(temp_value, current_value));
            } else {
                params_set(parameters, current_key, rb_ary_new_from_args(2, temp_value, current_value));
            }
        } else {
            params_set(parameters, current_key, current_value);
        }
    }

    action array_parameter_value {
        current_value = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_value = rb_funcall(unescaper, rb_intern("call"), 1, current_value);

        temp_value = params_access(parameters, current_key);

        if (RTEST(temp_value)) {
            if (RTEST(rb_obj_is_kind_of(temp_value, rb_cArray))) {
                params_set(parameters, current_key, rb_funcall(temp_value, rb_intern("concat"), 1, rb_str_split(current_value, ",")));
            } else {
                params_set(parameters, current_key, rb_funcall(rb_ary_new_from_args(1, temp_value), rb_intern("concat"), 1, rb_str_split(current_value, ",")));
            }
        } else {
            params_set(parameters, current_key, rb_str_split(current_value, ","));
        }
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

static VALUE make_params(VALUE self) {
    return rb_funcall(rb_iv_get(self, "@params_class"),
                      rb_intern("new"),
                      1,
                      rb_iv_get(self, "@key_space_limit"));
}

static VALUE parse(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator, unescaper;
    rb_scan_args(argc, argv, "11&", &query_string, &separator, &unescaper);
    // TODO: how to pass separator to Ragel?

    if (NIL_P(query_string)) query_string = rb_obj_freeze(rb_str_new_cstr(""));

    rb_encoding *encoding = rb_enc_get(query_string);
    const char *p = RSTRING_PTR(query_string);
    const char *pe = p + RSTRING_LEN(query_string);
    const char *eof = pe;
    const char *buffer;
    int cs = 0, encoded = 0;
    VALUE current_key = Qnil, current_value = Qnil, temp_value = Qnil;
    VALUE parameters = make_params(self);

    if (NIL_P(unescaper)) {
        unescaper = rb_funcall(rb_obj_class(self), rb_intern("method"), 1, ID2SYM(rb_intern("unescape")));
    }

    %%{
        write init;
        write exec;
    }%%

    return params_to_hash(parameters);
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

static VALUE new_space_limit(VALUE self, VALUE key_space_limit) {
    return rb_funcall(rb_obj_class(self),
                      rb_intern("new"),
                      3,
                      rb_iv_get(self, "@params_class"),
                      key_space_limit,
                      rb_iv_get(self, "@param_depth_limit"));
}

static VALUE new_depth_limit(VALUE self, VALUE param_depth_limit) {
    return rb_funcall(rb_obj_class(self),
                      rb_intern("new"),
                      3,
                      rb_iv_get(self, "@params_class"),
                      rb_iv_get(self, "@key_space_limit"),
                      param_depth_limit);
}

static VALUE check_types(RB_BLOCK_CALL_FUNC_ARGLIST(args, self)) {
    VALUE h = rb_ary_entry(args, 0);
    VALUE part = rb_ary_entry(args, 1);

    if (RSTRING_LEN(part) == 0) {
        rb_funcall(rb_current_receiver(), rb_intern("next"), 1, h);
    }

    if (!(RTEST(rb_obj_is_kind_of(h, rb_iv_get(self, "@params_class"))) && RTEST(rb_hash_aref(h, part)))) {
        return Qfalse;
    }

    return rb_hash_aref(h, part);
}

static VALUE params_hash_has_key(VALUE self, VALUE hash, VALUE key) {
    VALUE regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("\\[\\]")));
    if (RTEST(rb_funcall(regex, rb_intern("match?"), 1, key))) return Qfalse;

    VALUE split_regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("[\\[\\]]+")));
    VALUE args[1];
    args[0] = hash;

    rb_block_call(rb_funcall(key, rb_intern("split"), 1, split_regex), rb_intern("inject"), 1, args, check_types, self);
    return Qtrue;
}

static VALUE normalize_params(VALUE self, VALUE params, VALUE name, VALUE value, VALUE depth) {
    if (NUM2INT(depth) <= 0) rb_raise(rb_eRangeError, "depth must be greater than zero");

    VALUE regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("\\A[\\[\\]]*([^\\[\\]]+)\\]*")));
    VALUE regex_2 = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("^\\[\\]\\[([^\\[\\]]+)\\]$")));
    VALUE regex_3 = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("^\\[\\](.+)$")));
    VALUE match_data = rb_funcall(regex, rb_intern("match"), 1, name);
    VALUE k = rb_funcall(match_data, rb_intern("[]"), 1, INT2NUM(0));
    VALUE after = rb_funcall(match_data, rb_intern("post_match"), 0);
    VALUE entry = Qnil, array_entry = Qnil;

    if (NIL_P(k)) k = rb_obj_freeze(rb_str_new_cstr(""));
    if (NIL_P(after)) after = rb_obj_freeze(rb_str_new_cstr(""));

    if (RSTRING_LEN(k) == 0) {
        if (!NIL_P(value) && strcmp(RSTRING_PTR(name), "[]") == 0) {
            rb_funcall(value, rb_intern("to_ary"), 0);
        } else {
            return Qnil;
        }
    }

    if (strcmp(RSTRING_PTR(after), "") == 0) {
        rb_funcall(params, rb_intern("[]="), 2, k, value);
    } else if (strcmp(RSTRING_PTR(after), "[") == 0) {
        rb_funcall(params, rb_intern("[]="), 2, name, value);
    } else if (strcmp(RSTRING_PTR(after), "[]") == 0) {
        if (NIL_P(entry = params_access(params, k))) {
            rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_new());
        }

        if (!RTEST(rb_obj_is_kind_of(entry, rb_cArray))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Array (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_push(entry, value));
    } else if (RTEST(match_data = rb_funcall(regex_2, rb_intern("match"), 1, after)) || RTEST(match_data = rb_funcall(regex_3, rb_intern("match"), 1, after))) {
        VALUE child_key = rb_funcall(match_data, rb_intern("[]"), 1, INT2NUM(0));

        if (NIL_P(entry = params_access(params, k))) rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_new());

        if (!RTEST(rb_obj_is_kind_of(entry, rb_cArray))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Array (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        if (RTEST(rb_obj_is_kind_of(array_entry = rb_ary_entry(entry, RARRAY_LEN(entry) - 1), rb_iv_get(self, "@params_class"))) && !RTEST(params_hash_has_key(self, array_entry, child_key))) {
            normalize_params(self, array_entry, child_key, value, INT2NUM(NUM2INT(depth) - 1));
        } else {
            rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_push(entry, normalize_params(self, make_params(self), child_key, value, INT2NUM(NUM2INT(depth) - 1))));
        }
    } else {
        if (NIL_P(entry = params_access(params, k))) rb_funcall(params, rb_intern("[]="), 2, k, make_params(self));

        if (!RTEST(rb_obj_is_kind_of(entry, rb_iv_get(self, "@params_class")))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Hash (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        rb_funcall(params, rb_intern("[]="), 2, k, normalize_params(self, entry, after, value, INT2NUM(NUM2INT(depth) - 1)));
    }

    return params;
}

void Init_parser(VALUE rb_mQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mQueryParser, "Parser", rb_cObject);
    rb_eParameterTypeError = rb_define_class_under(rb_cParser, "ParameterTypeError", rb_eTypeError);

    rb_cParams = rb_const_get(rb_mQueryParser, rb_intern("Params"));
    rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));

    rb_funcall(rb_cParser, rb_intern("attr_reader"), 2, ID2SYM(rb_intern("key_space_limit")), ID2SYM(rb_intern("param_depth_limit")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 3);
    rb_define_method(rb_cParser, "parse_query", parse, -1);
    rb_define_method(rb_cParser, "new_space_limit", new_space_limit, 1);
    rb_define_method(rb_cParser, "new_depth_limit", new_depth_limit, 1);
    rb_define_method(rb_cParser, "make_params", make_params, 0);
    rb_define_method(rb_cParser, "normalize_params", normalize_params, 4);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
    rb_define_singleton_method(rb_cParser, "make_default", make_default, 2);
}
