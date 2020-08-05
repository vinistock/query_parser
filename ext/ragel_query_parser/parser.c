
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


#line 65 "ext/ragel_query_parser/parser.rl"



#line 22 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 9;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 68 "ext/ragel_query_parser/parser.rl"

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
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st2;
tr16:
#line 25 "ext/ragel_query_parser/parser.rl"
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
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 106 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr2;
		case 37: goto tr3;
		case 43: goto tr4;
		case 93: goto tr2;
		case 95: goto tr2;
		case 126: goto tr2;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
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
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st3;
tr4:
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
tr7:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 155 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr6;
		case 43: goto tr7;
		case 61: goto tr8;
		case 93: goto st3;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
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
tr3:
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
tr6:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 198 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st5;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st5;
	} else
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st3;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st3;
	} else
		goto st3;
	goto st0;
tr8:
#line 25 "ext/ragel_query_parser/parser.rl"
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
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 243 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr10;
		case 37: goto tr11;
		case 43: goto tr12;
		case 93: goto tr10;
		case 95: goto tr10;
		case 126: goto tr10;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr10;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr10;
		} else if ( (*p) >= 64 )
			goto tr10;
	} else
		goto tr10;
	goto st0;
tr17:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st9;
tr10:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st9;
tr12:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 300 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st9;
		case 37: goto tr15;
		case 38: goto tr16;
		case 43: goto tr17;
		case 63: goto tr16;
		case 93: goto st9;
		case 95: goto st9;
		case 126: goto st9;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 59 )
			goto st9;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st9;
	} else
		goto st9;
	goto st0;
tr15:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
tr11:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 20 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 345 "ext/ragel_query_parser/parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st8;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st8;
	} else
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st9;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st9;
	} else
		goto st9;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 9: 
#line 25 "ext/ragel_query_parser/parser.rl"
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
#line 400 "ext/ragel_query_parser/parser.c"
	}
	}

	_out: {}
	}

#line 93 "ext/ragel_query_parser/parser.rl"


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
