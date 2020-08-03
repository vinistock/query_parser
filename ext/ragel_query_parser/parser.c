
#line 1 "ext/ragel_query_parser/parser.rl"
/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"


#line 51 "ext/ragel_query_parser/parser.rl"



#line 18 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 5;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 54 "ext/ragel_query_parser/parser.rl"

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
    int cs = 0, reading_value = 0;
    VALUE current_key = Qnil;

    if (NIL_P(unescaper)) {
        unescaper = rb_funcall(rb_obj_class(self), rb_intern("method"), 1, rb_obj_freeze(rb_str_new_cstr("unescape")));
    }

    
#line 50 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 55 "ext/ragel_query_parser/parser.c"
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
#line 32 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st2;
tr7:
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_obj_freeze(
            rb_funcall(unescaper, rb_intern("call"), 1, rb_enc_str_new(buffer, p - buffer, encoding))
        );

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
#line 32 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 98 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr2;
		case 93: goto tr2;
		case 95: goto tr2;
		case 126: goto tr2;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 37 )
			goto tr2;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr2;
		} else if ( (*p) >= 64 )
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
#line 127 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 61: goto tr4;
		case 93: goto st3;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 37 )
			goto st3;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st3;
		} else if ( (*p) >= 64 )
			goto st3;
	} else
		goto st3;
	goto st0;
tr4:
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_obj_freeze(
            rb_funcall(unescaper, rb_intern("call"), 1, rb_enc_str_new(buffer, p - buffer, encoding))
        );

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 165 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr5;
		case 93: goto tr5;
		case 95: goto tr5;
		case 126: goto tr5;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 37 )
			goto tr5;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr5;
		} else if ( (*p) >= 64 )
			goto tr5;
	} else
		goto tr5;
	goto st0;
tr5:
#line 36 "ext/ragel_query_parser/parser.rl"
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
#line 198 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st5;
		case 38: goto tr7;
		case 63: goto tr7;
		case 93: goto st5;
		case 95: goto st5;
		case 126: goto st5;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 59 )
			goto st5;
	} else if ( (*p) > 91 ) {
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
        VALUE string = rb_obj_freeze(
            rb_funcall(unescaper, rb_intern("call"), 1, rb_enc_str_new(buffer, p - buffer, encoding))
        );

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
	break;
#line 240 "ext/ragel_query_parser/parser.c"
	}
	}

	_out: {}
	}

#line 79 "ext/ragel_query_parser/parser.rl"


    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    rb_iv_set(self, "@parameters", rb_hash_new());
    return self;
}

static VALUE unescape(VALUE self, VALUE string) {
    VALUE rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    VALUE utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));
    VALUE rb_mUri = rb_const_get(rb_cObject, rb_intern("URI"));
    return rb_funcall(rb_mUri, rb_intern("decode_www_form_component"), 2, string, utf_8);
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    // TODO: better way of defining attr_reader from C?
    rb_funcall(rb_cParser, rb_intern("attr_reader"), 1, rb_obj_freeze(rb_str_new_cstr("parameters")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
}
