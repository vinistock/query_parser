
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


#line 71 "ext/ragel_query_parser/parser.rl"



#line 21 "ext/ragel_query_parser/parser.c"
static const int parser_start = 0;
static const int parser_first_final = 12;
static const int parser_error = -1;

static const int parser_en_main = 0;


#line 74 "ext/ragel_query_parser/parser.rl"

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
    int cs = 0, reading_value = 0, array_parameter = 0, encoded = 0;
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
tr66:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
#line 40 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
        array_parameter = 0;
    }
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 94 "ext/ragel_query_parser/parser.c"
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
		goto st16;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st1;
	goto st12;
tr31:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 141 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr26;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr27;
	goto tr25;
tr25:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 157 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr28;
	goto tr27;
tr27:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 171 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st15;
	goto st14;
tr28:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 185 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st16;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st14;
	goto st12;
tr26:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 201 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto tr26;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr27;
	goto tr31;
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
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
tr9:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 235 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr8;
		case 43: goto tr9;
		case 61: goto tr10;
		case 91: goto tr11;
		case 93: goto st3;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st3;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
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
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
tr8:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 279 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st16;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st5;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st17;
	} else
		goto st17;
	goto st12;
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
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 37 )
		goto tr26;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr32;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr33;
	} else
		goto tr33;
	goto tr25;
tr53:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st18;
tr55:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st18;
tr36:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st18;
tr32:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st18;
tr62:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 365 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st18;
		case 37: goto tr35;
		case 43: goto tr36;
		case 61: goto tr37;
		case 91: goto tr38;
		case 93: goto st18;
		case 95: goto st18;
		case 126: goto st18;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st18;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st18;
		} else if ( (*p) >= 64 )
			goto st18;
	} else
		goto st18;
	goto st14;
tr54:
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
tr35:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
tr61:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 419 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st16;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st20;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st17;
	} else
		goto st17;
	goto st12;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 37 )
		goto st15;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st18;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st18;
	} else
		goto st18;
	goto st14;
tr37:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st21;
tr63:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 496 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr40;
		case 37: goto tr41;
		case 43: goto tr42;
		case 93: goto tr40;
		case 95: goto tr40;
		case 126: goto tr40;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr40;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr40;
		} else if ( (*p) >= 64 )
			goto tr40;
	} else
		goto tr40;
	goto st14;
tr46:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st22;
tr40:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st22;
tr42:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st22;
tr58:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st22;
tr60:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st22;
tr48:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st22;
tr52:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 605 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st22;
		case 37: goto tr44;
		case 38: goto tr45;
		case 43: goto tr46;
		case 59: goto tr45;
		case 93: goto st22;
		case 95: goto st22;
		case 126: goto st22;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st22;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st22;
	} else
		goto st22;
	goto st14;
tr44:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st23;
tr41:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st23;
tr59:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st23;
tr50:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 680 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st16;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st24;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st25;
	} else
		goto st25;
	goto st12;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 37 )
		goto st15;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st22;
	} else
		goto st22;
	goto st14;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 37 )
		goto tr26;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr48;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr49;
	} else
		goto tr49;
	goto tr25;
tr49:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 732 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr48;
		case 37: goto tr50;
		case 38: goto tr51;
		case 43: goto tr52;
		case 59: goto tr51;
		case 93: goto tr48;
		case 95: goto tr48;
		case 126: goto tr48;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto tr48;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr48;
	} else
		goto tr48;
	goto tr27;
tr45:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
#line 40 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
        array_parameter = 0;
    }
	goto st27;
tr51:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
#line 40 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 0;
        array_parameter = 0;
    }
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 812 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr53;
		case 37: goto tr54;
		case 43: goto tr55;
		case 93: goto tr53;
		case 95: goto tr53;
		case 126: goto tr53;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr53;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr53;
		} else if ( (*p) >= 64 )
			goto tr53;
	} else
		goto tr53;
	goto st14;
tr38:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st28;
tr64:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 883 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st18;
		case 37: goto tr35;
		case 43: goto tr36;
		case 61: goto tr37;
		case 91: goto tr38;
		case 93: goto st29;
		case 95: goto st18;
		case 126: goto st18;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st18;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st18;
		} else if ( (*p) >= 64 )
			goto st18;
	} else
		goto st18;
	goto st14;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 33: goto st18;
		case 37: goto tr35;
		case 43: goto tr36;
		case 61: goto tr57;
		case 91: goto tr38;
		case 93: goto st18;
		case 95: goto st18;
		case 126: goto st18;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st18;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st18;
		} else if ( (*p) >= 64 )
			goto st18;
	} else
		goto st18;
	goto st14;
tr57:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 957 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr58;
		case 37: goto tr59;
		case 43: goto tr60;
		case 93: goto tr58;
		case 95: goto tr58;
		case 126: goto tr58;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr58;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr58;
		} else if ( (*p) >= 64 )
			goto tr58;
	} else
		goto tr58;
	goto st14;
tr33:
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 988 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr32;
		case 37: goto tr61;
		case 43: goto tr62;
		case 61: goto tr63;
		case 91: goto tr64;
		case 93: goto tr32;
		case 95: goto tr32;
		case 126: goto tr32;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr32;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr32;
		} else if ( (*p) >= 64 )
			goto tr32;
	} else
		goto tr32;
	goto tr27;
tr10:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 1036 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr14;
		case 37: goto tr15;
		case 43: goto tr16;
		case 93: goto tr14;
		case 95: goto tr14;
		case 126: goto tr14;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr14;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr14;
		} else if ( (*p) >= 64 )
			goto tr14;
	} else
		goto tr14;
	goto st1;
tr67:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st32;
tr14:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st32;
tr16:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st32;
tr22:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st32;
tr24:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 1129 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st32;
		case 37: goto tr65;
		case 38: goto tr66;
		case 43: goto tr67;
		case 59: goto tr66;
		case 93: goto st32;
		case 95: goto st32;
		case 126: goto st32;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st32;
	} else if ( (*p) > 91 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st32;
	} else
		goto st32;
	goto st1;
tr65:
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
tr15:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 49 "ext/ragel_query_parser/parser.rl"
	{
        encoded = 1;
    }
	goto st7;
tr23:
#line 45 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
    }
#line 57 "ext/ragel_query_parser/parser.rl"
	{
        reading_value = 1;
        array_parameter = 1;
    }
#line 16 "ext/ragel_query_parser/parser.rl"
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
#line 1194 "ext/ragel_query_parser/parser.c"
	if ( (*p) == 37 )
		goto st16;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st8;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st25;
	} else
		goto st25;
	goto st12;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 37 )
		goto st2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st32;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st32;
	} else
		goto st32;
	goto st1;
tr11:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 1246 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr8;
		case 43: goto tr9;
		case 61: goto tr10;
		case 91: goto tr11;
		case 93: goto st10;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st3;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st3;
		} else if ( (*p) >= 64 )
			goto st3;
	} else
		goto st3;
	goto st1;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr8;
		case 43: goto tr9;
		case 61: goto tr21;
		case 91: goto tr11;
		case 93: goto st3;
		case 95: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st3;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st3;
		} else if ( (*p) >= 64 )
			goto st3;
	} else
		goto st3;
	goto st1;
tr21:
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 1320 "ext/ragel_query_parser/parser.c"
	switch( (*p) ) {
		case 33: goto tr22;
		case 37: goto tr23;
		case 43: goto tr24;
		case 93: goto tr22;
		case 95: goto tr22;
		case 126: goto tr22;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr22;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 91 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr22;
		} else if ( (*p) >= 64 )
			goto tr22;
	} else
		goto tr22;
	goto st1;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 22: 
	case 32: 
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	break;
	case 12: 
	case 13: 
	case 16: 
	case 17: 
	case 25: 
	case 31: 
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	break;
	case 26: 
#line 53 "ext/ragel_query_parser/parser.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 21 "ext/ragel_query_parser/parser.rl"
	{
        VALUE string = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) {
            string = rb_funcall(unescaper, rb_intern("call"), 1, string);
        }

        if (reading_value) {
            if (array_parameter) {
                rb_funcall(current_key, rb_intern("delete!"), 1, rb_obj_freeze(rb_str_new_cstr("[]")));
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), rb_str_split(string, ","));
            } else {
                rb_hash_aset(rb_iv_get(self, "@parameters"), rb_str_intern(rb_obj_freeze(current_key)), string);
            }
        } else {
            current_key = string;
        }
    }
	break;
#line 1438 "ext/ragel_query_parser/parser.c"
	}
	}

	}

#line 99 "ext/ragel_query_parser/parser.rl"


    return rb_iv_get(self, "@parameters");
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
