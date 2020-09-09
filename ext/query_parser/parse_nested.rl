/**
  * parse_nested_query implementation
  *
  * Copyright (c) 2020 Vinicius Stock
  * Available under the MIT License
  */

#include "parse_nested.h"

%%{
    machine nested_parser;

    main := alpha;
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
