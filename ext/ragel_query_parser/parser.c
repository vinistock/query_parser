
#line 1 "ext/ragel_query_parser/parser.rl"
/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"

static VALUE rb_mEncoding;
static VALUE utf_8;
static VALUE rb_mUri;


#line 57 "ext/ragel_query_parser/parser.rl"



#line 22 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 8;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 60 "ext/ragel_query_parser/parser.rl"

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
    int cs = 0, reading_value = 0, encoded = 0;
    VALUE current_key = Qnil;

    if (NIL_P(unescaper)) {
        unescaper = rb_funcall(rb_obj_class(self), rb_intern("method"), 1, rb_obj_freeze(rb_str_new_cstr("unescape")));
    }

    
#line 54 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 59 "ext/ragel_query_parser/parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr15:
#line 22 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        string = rb_obj_freeze(string);

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
#line 38 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 91 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr0;
		case 37: goto tr2;
		case 43: goto tr3;
		case 93: goto tr0;
		case 95: goto tr0;
		case 126: goto tr0;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr0;
		} else if ( (*p) >= 64 )
			goto tr0;
	} else
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st2;
tr3:
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st2;
tr6:
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 143 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st2;
		case 37: goto tr5;
		case 43: goto tr6;
		case 61: goto tr7;
		case 93: goto st2;
		case 95: goto st2;
		case 126: goto st2;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st2;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st2;
		} else if ( (*p) >= 64 )
			goto st2;
	} else
		goto st2;
	goto st0;
tr2:
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
tr5:
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 186 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st4;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st4;
	} else
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st2;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st2;
	} else
		goto st2;
	goto st0;
tr7:
#line 22 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        string = rb_obj_freeze(string);

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 231 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr9;
		case 37: goto tr10;
		case 43: goto tr11;
		case 93: goto tr9;
		case 95: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr9;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else if ( (*p) >= 64 )
			goto tr9;
	} else
		goto tr9;
	goto st0;
tr16:
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st8;
tr9:
#line 42 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st8;
tr11:
#line 42 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 288 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st8;
		case 37: goto tr14;
		case 38: goto tr15;
		case 43: goto tr16;
		case 59: goto tr15;
		case 93: goto st8;
		case 95: goto st8;
		case 126: goto st8;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st8;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st8;
	} else
		goto st8;
	goto st0;
tr14:
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st6;
tr10:
#line 42 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 17 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 46 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 333 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st7;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st7;
	} else
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st8;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st8;
	} else
		goto st8;
	goto st0;
	}
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 8: 
#line 22 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        string = rb_obj_freeze(string);

        if (reading_value) {
            rb_hash_aset(rb_iv_get(self, "@parameters"), current_key, string);
        } else {
            current_key = rb_str_intern(string);
        }
    }
	break;
#line 388 "ext/ragel_query_parser/parser.c"
	}
	}

	_out: {}
	}

#line 85 "ext/ragel_query_parser/parser.rl"


    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    rb_iv_set(self, "@parameters", rb_hash_new());
    return self;
}

static VALUE unescape(VALUE self, VALUE string) {
    return rb_funcall(rb_mUri, rb_intern("decode_www_form_component"), 2, string, utf_8);
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));
    rb_mUri = rb_const_get(rb_cObject, rb_intern("URI"));

    // TODO: better way of defining attr_reader from C?
    rb_funcall(rb_cParser, rb_intern("attr_reader"), 1, rb_obj_freeze(rb_str_new_cstr("parameters")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
}
