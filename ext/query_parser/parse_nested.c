
#line 1 "ext/query_parser/parse_nested.rl"
/**
  * parse_nested_query implementation
  *
  * Copyright (c) 2020 Vinicius Stock
  * Available under the MIT License
  */

#include "parse_nested.h"


#line 14 "ext/query_parser/parse_nested.rl"



#line 18 "ext/query_parser/parse_nested.c"
static const int nested_parser_start = 1;
static const int nested_parser_first_final = 2;
static const int nested_parser_error = 0;

static const int nested_parser_en_main = 1;


#line 17 "ext/query_parser/parse_nested.rl"

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

    
#line 43 "ext/query_parser/parse_nested.c"
	{
	cs = nested_parser_start;
	}

#line 48 "ext/query_parser/parse_nested.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st2;
	} else if ( (*p) >= 65 )
		goto st2;
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 35 "ext/query_parser/parse_nested.rl"


    return rb_funcall(parameters, rb_intern("to_h"), 0);
}
