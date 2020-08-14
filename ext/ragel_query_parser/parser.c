
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


#line 61 "ext/ragel_query_parser/parser.rl"



#line 21 "ext/ragel_query_parser/parser.c"
static const int parser_start = 0;
static const int parser_first_final = 9;
static const int parser_error = -1;

static const int parser_en_main = 0;


#line 64 "ext/ragel_query_parser/parser.rl"

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

    
#line 53 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 58 "ext/ragel_query_parser/parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr53:
#line 21 "ext/ragel_query_parser/parser.rl"
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
#line 37 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 90 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr1;
		case 37: goto tr2;
		case 43: goto tr3;
		case 93: goto tr1;
		case 95: goto tr1;
		case 126: goto tr1;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr1;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr1;
		} else if ( (*p) >= 64 )
			goto tr1;
	} else
		goto tr1;
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 37 )
		goto st2;
	goto st1;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 37 )
		goto st13;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st1;
	goto st9;
tr25:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 137 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr20;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr21;
	goto tr19;
tr19:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 153 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr22;
	goto tr21;
tr21:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 167 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st12;
	goto st11;
tr22:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 181 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st13;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st11;
	goto st9;
tr20:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 197 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr20;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr21;
	goto tr25;
tr1:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st3;
tr3:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
tr9:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 231 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr8;
		case 43: goto tr9;
		case 61: goto tr10;
		case 93: goto st3;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st3;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st3;
		} else if ( (*p) >= 64 )
			goto st3;
	} else
		goto st3;
	goto st1;
tr2:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
tr8:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 274 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st13;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st5;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st14;
	} else
		goto st14;
	goto st9;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 37 )
		goto st2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st3;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st3;
	} else
		goto st3;
	goto st1;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 37 )
		goto tr20;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr26;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr27;
	} else
		goto tr27;
	goto tr19;
tr46:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st15;
tr48:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st15;
tr30:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st15;
tr26:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st15;
tr50:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 360 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st15;
		case 37: goto tr29;
		case 43: goto tr30;
		case 61: goto tr31;
		case 93: goto st15;
		case 95: goto st15;
		case 126: goto st15;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st15;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st15;
		} else if ( (*p) >= 64 )
			goto st15;
	} else
		goto st15;
	goto st11;
tr47:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st16;
tr29:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st16;
tr49:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 413 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st13;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st17;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st14;
	} else
		goto st14;
	goto st9;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 37 )
		goto st12;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st15;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st15;
	} else
		goto st15;
	goto st11;
tr31:
#line 21 "ext/ragel_query_parser/parser.rl"
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
	goto st18;
tr51:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
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
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 484 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr33;
		case 37: goto tr34;
		case 43: goto tr35;
		case 93: goto tr33;
		case 95: goto tr33;
		case 126: goto tr33;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr33;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr33;
		} else if ( (*p) >= 64 )
			goto tr33;
	} else
		goto tr33;
	goto st11;
tr39:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
tr33:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st19;
tr35:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
tr41:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st19;
tr45:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 557 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st19;
		case 37: goto tr37;
		case 38: goto tr38;
		case 43: goto tr39;
		case 59: goto tr38;
		case 93: goto st19;
		case 95: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st19;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st19;
	} else
		goto st19;
	goto st11;
tr37:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st20;
tr34:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st20;
tr43:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 612 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st13;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st21;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st22;
	} else
		goto st22;
	goto st9;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 37 )
		goto st12;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st19;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st19;
	} else
		goto st19;
	goto st11;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 37 )
		goto tr20;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr41;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr42;
	} else
		goto tr42;
	goto tr19;
tr42:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 664 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr41;
		case 37: goto tr43;
		case 38: goto tr44;
		case 43: goto tr45;
		case 59: goto tr44;
		case 93: goto tr41;
		case 95: goto tr41;
		case 126: goto tr41;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto tr41;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr41;
	} else
		goto tr41;
	goto tr21;
tr38:
#line 21 "ext/ragel_query_parser/parser.rl"
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
#line 37 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st24;
tr44:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
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
#line 37 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
    }
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 736 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr46;
		case 37: goto tr47;
		case 43: goto tr48;
		case 93: goto tr46;
		case 95: goto tr46;
		case 126: goto tr46;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr46;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr46;
		} else if ( (*p) >= 64 )
			goto tr46;
	} else
		goto tr46;
	goto st11;
tr27:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 767 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr26;
		case 37: goto tr49;
		case 43: goto tr50;
		case 61: goto tr51;
		case 93: goto tr26;
		case 95: goto tr26;
		case 126: goto tr26;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr26;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr26;
		} else if ( (*p) >= 64 )
			goto tr26;
	} else
		goto tr26;
	goto tr21;
tr10:
#line 21 "ext/ragel_query_parser/parser.rl"
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
#line 811 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr13;
		case 37: goto tr14;
		case 43: goto tr15;
		case 93: goto tr13;
		case 95: goto tr13;
		case 126: goto tr13;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr13;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr13;
		} else if ( (*p) >= 64 )
			goto tr13;
	} else
		goto tr13;
	goto st1;
tr54:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st26;
tr13:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st26;
tr15:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 868 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st26;
		case 37: goto tr52;
		case 38: goto tr53;
		case 43: goto tr54;
		case 59: goto tr53;
		case 93: goto st26;
		case 95: goto st26;
		case 126: goto st26;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st26;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st26;
	} else
		goto st26;
	goto st1;
tr52:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
tr14:
#line 41 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 913 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st13;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st8;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st22;
	} else
		goto st22;
	goto st9;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 37 )
		goto st2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st26;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st26;
	} else
		goto st26;
	goto st1;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 19: 
	case 26: 
#line 21 "ext/ragel_query_parser/parser.rl"
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
	case 9: 
	case 10: 
	case 13: 
	case 14: 
	case 22: 
	case 25: 
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	break;
	case 23: 
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
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
#line 1025 "ext/ragel_query_parser/parser.c"
	}
	}

	}

#line 89 "ext/ragel_query_parser/parser.rl"


    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    rb_iv_set(self, "@parameters", rb_hash_new());
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

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));

    // TODO: better way of defining attr_reader from C?
    rb_funcall(rb_cParser, rb_intern("attr_reader"), 1, rb_obj_freeze(rb_str_new_cstr("parameters")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
}
