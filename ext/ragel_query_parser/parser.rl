/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"

%%{
    machine parser;

    ##
    # Actions
    ##
    action start_word {
        buffer = p;
    }

    action end_word {
        if (reading_value) {
            VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(rb_enc_str_new(buffer, p - buffer, encoding));
        }
    }

    action start_separator {
        reading_value = 0;
    }

    action end_key_value_separator {
        reading_value = 1;
    }

    ##
    # Token action associations
    ##
    parameter_separator = ("?" | "&") >start_separator;
    key_value_separator = "=" %end_key_value_separator;
    parameter_content = (alnum | "-" | "." | "_" | "~" | ":" | "/" | "#" | "[" | "]" | "@" | "!" | "$" | "'" | "(" | ")" | "*" | "+" | "," | ";" | "%")+ >start_word %end_word;

    ##
    # Main machine definition
    ##
    main := (parameter_separator parameter_content key_value_separator parameter_content)+;
}%%

%% write data;

/*
    parser = RagelQueryParser.new
    parser.parse(query, separator = "&", unescaper = -> {})
*/
static VALUE parse(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator, unescaper;
    rb_scan_args(argc, argv, "11&", &query_string, &separator, &unescaper);
    // TODO: use separator and unescaper

    rb_encoding *encoding = rb_enc_get(query_string);
    const char *p = RSTRING_PTR(query_string);
    const char *pe = p + RSTRING_LEN(query_string);
    const char *eof = pe;
    const char *buffer;
    int cs = 0, reading_value = 0;
    VALUE current_key = Qnil;

    %%{
        write init;
        write exec;
    }%%

    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    rb_iv_set(self, "@parameters", rb_hash_new());
    return self;
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    // TODO: better way of defining attr_reader from C?
    rb_funcall(rb_cParser, rb_intern("attr_reader"), 1, rb_str_new_cstr("parameters"));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);
}
