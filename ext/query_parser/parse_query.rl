/**
  * parse_query implementation
  *
  * Copyright (c) 2020 Vinicius Stock
  * Available under the MIT License
  */

#include "parse_query.h"

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

        temp_value = rb_funcall(parameters, rb_intern("[]"), 1, current_key);

        if (RTEST(temp_value)) {
            if (RTEST(rb_obj_is_kind_of(temp_value, rb_cArray))) {
                rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_ary_push(temp_value, current_value));
            } else {
                rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_ary_new_from_args(2, temp_value, current_value));
            }
        } else {
            rb_funcall(parameters, rb_intern("[]="), 2, current_key, current_value);
        }
    }

    action array_parameter_value {
        current_value = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_value = rb_funcall(unescaper, rb_intern("call"), 1, current_value);

        temp_value = rb_funcall(parameters, rb_intern("[]"), 1, current_key);

        if (RTEST(temp_value)) {
            if (RTEST(rb_obj_is_kind_of(temp_value, rb_cArray))) {
                rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_funcall(temp_value, rb_intern("concat"), 1, rb_str_split(current_value, ",")));
            } else {
                rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_funcall(rb_ary_new_from_args(1, temp_value), rb_intern("concat"), 1, rb_str_split(current_value, ",")));
            }
        } else {
            rb_funcall(parameters, rb_intern("[]="), 2, current_key, rb_str_split(current_value, ","));
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

VALUE parse_query(int argc, VALUE* argv, VALUE self) {
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
    VALUE parameters = rb_funcall(self, rb_intern("make_params"), 0);

    if (NIL_P(unescaper)) {
        unescaper = rb_funcall(rb_obj_class(self), rb_intern("method"), 1, ID2SYM(rb_intern("unescape")));
    }

    %%{
        write init;
        write exec;
    }%%

    return rb_funcall(parameters, rb_intern("to_h"), 0);
}

