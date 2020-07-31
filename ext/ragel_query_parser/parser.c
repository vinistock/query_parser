
#line 1 "ext/ragel_query_parser/parser.rl"
/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"


#line 48 "ext/ragel_query_parser/parser.rl"



#line 18 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 5;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 51 "ext/ragel_query_parser/parser.rl"

/*
    parser = RagelQueryParser.new
    parser.parse(query, separator = "&", unescaper = -> {})
*/
static VALUE parse(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator, unescaper;
    rb_scan_args(argc, argv, "11&", &query_string, &separator, &unescaper);

    rb_encoding *encoding = rb_enc_get(query_string);
    const char *p = RSTRING_PTR(query_string);
    const char *pe = p + RSTRING_LEN(query_string);
    const char *eof = pe;
    const char *buffer;
    int cs = 0, reading_value = 0;
    VALUE current_key = Qnil;

    
#line 45 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 50 "ext/ragel_query_parser/parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 38: goto tr0;
		case 63: goto tr0;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 29 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 75 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr2;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr2;
	} else
		goto tr2;
	goto st0;
tr2:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        buffer = p;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 95 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 61 )
		goto tr4;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st3;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st3;
	} else
		goto st3;
	goto st0;
tr4:
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        if (reading_value) {
            VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(rb_enc_str_new(buffer, p - buffer, encoding));
        }
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 122 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr5;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr5;
	} else
		goto tr5;
	goto st0;
tr5:
#line 33 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        buffer = p;
    }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 146 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st5;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st5;
	} else
		goto st5;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 5: 
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        if (reading_value) {
            VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(rb_enc_str_new(buffer, p - buffer, encoding));
        }
    }
	break;
#line 177 "ext/ragel_query_parser/parser.c"
	}
	}

	_out: {}
	}

#line 71 "ext/ragel_query_parser/parser.rl"


    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    rb_iv_set(self, "@parameters", rb_hash_new());
    return self;
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    rb_funcall(rb_cParser, rb_intern("attr_reader"), 1, rb_str_new_cstr("parameters"));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);
}
