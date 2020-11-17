/**
  * parse_nested_query implementation
  *
  * Copyright (c) 2020 Vinicius Stock
  * Available under the MIT License
  */

#include "parse_nested.h"

%%{
    machine nested_parser;

    action start_word {
        encoded = 0;
        buffer = p;
    }

    action set_encoded {
        encoded = 1;
    }

    action parameter_key {
        if (NIL_P(current_key)) {
            current_key = rb_enc_str_new(buffer, p - buffer, encoding);

            if (encoded) current_key = unescape(self, current_key);

            current_key = rb_obj_freeze(current_key);
        } else {
            rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_hash_new()); 
        }
    }

    parameter_separator = [&;];
    encoded_content = ("+" | "%" xdigit xdigit) >set_encoded;
    parameter_content = (alnum | [\-._~:/#@!$'()*,] | encoded_content)+ >start_word;
    regular_parameter = parameter_content %parameter_key "=" parameter_content %regular_parameter_value;
    array_parameter = parameter_content %parameter_key "[]=" parameter_content %array_parameter_value;
    nested_parameter = parameter_content %parameter_key ([parameter_content %parameter_key])+ = parameter_content %regular_parameter_value;
    parameter = array_parameter | regular_parameter;

    main := parameter (parameter_separator parameter)*;
}%%

%% write data;

VALUE parse_nested_query(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator;
    rb_scan_args(argc, argv, "11", &query_string, &separator);
    // TODO: how to pass separator to Ragel?

    rb_encoding *encoding = rb_enc_get(query_string);
    const char *p = RSTRING_PTR(query_string);
    const char *pe = p + RSTRING_LEN(query_string);
    const char *eof = pe;
    const char *buffer;
    int cs = 0, encoded = 0;
    VALUE current_key = Qnil, current_value = Qnil, temp_value = Qnil;
    VALUE parameters = rb_funcall(self, rb_intern("make_params"), 0);

    if (!(NIL_P(query_string) || RSTRING_LEN(query_string) == 0)) {
        %%{
            write init;
            write exec;
        }%%
    }

    return rb_funcall(parameters, rb_intern("to_h"), 0);
}
