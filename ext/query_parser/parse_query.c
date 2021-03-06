
#line 1 "ext/query_parser/parse_query.rl"
/**
  * parse_query implementation
  *
  * Copyright (c) 2020 Vinicius Stock
  * Available under the MIT License
  */

#include "parse_query.h"


#line 79 "ext/query_parser/parse_query.rl"



#line 18 "ext/query_parser/parse_query.c"
static const int parser_start = 0;
static const int parser_first_final = 14;
static const int parser_error = -1;

static const int parser_en_main = 0;


#line 82 "ext/query_parser/parse_query.rl"

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

    
#line 49 "ext/query_parser/parse_query.c"
	{
	cs = parser_start;
	}

#line 54 "ext/query_parser/parse_query.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr79:
#line 34 "ext/query_parser/parse_query.rl"
	{
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
	goto st0;
tr82:
#line 52 "ext/query_parser/parse_query.rl"
	{
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
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 104 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr1;
		case 37: goto tr2;
		case 43: goto tr3;
		case 95: goto tr1;
		case 126: goto tr1;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr1;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
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
		goto st18;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st1;
	goto st14;
tr34:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 150 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto tr29;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr30;
	goto tr28;
tr28:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 166 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto tr31;
	goto tr30;
tr30:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 180 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st17;
	goto st16;
tr31:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 194 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st16;
	goto st14;
tr29:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 210 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto tr29;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr30;
	goto tr34;
tr1:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st3;
tr3:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st3;
tr9:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 244 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st3;
		case 37: goto tr8;
		case 43: goto tr9;
		case 61: goto tr10;
		case 91: goto tr11;
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
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st4;
tr8:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 287 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st5;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st19;
	} else
		goto st19;
	goto st14;
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
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 37 )
		goto tr29;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr35;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr36;
	} else
		goto tr36;
	goto tr28;
tr56:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st20;
tr58:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st20;
tr39:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st20;
tr35:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st20;
tr75:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 373 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st20;
		case 37: goto tr38;
		case 43: goto tr39;
		case 61: goto tr40;
		case 91: goto tr41;
		case 95: goto st20;
		case 126: goto st20;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto st20;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 64 )
			goto st20;
	} else
		goto st20;
	goto st16;
tr57:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st21;
tr38:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st21;
tr74:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 426 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st19;
	} else
		goto st19;
	goto st14;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 37 )
		goto st17;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st20;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st20;
	} else
		goto st20;
	goto st16;
tr40:
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st23;
tr76:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 481 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr43;
		case 37: goto tr44;
		case 43: goto tr45;
		case 95: goto tr43;
		case 126: goto tr43;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr43;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr43;
		} else if ( (*p) >= 64 )
			goto tr43;
	} else
		goto tr43;
	goto st16;
tr43:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st24;
tr45:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st24;
tr49:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st24;
tr51:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st24;
tr55:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 545 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st24;
		case 37: goto tr47;
		case 38: goto tr48;
		case 43: goto tr49;
		case 59: goto tr48;
		case 95: goto st24;
		case 126: goto st24;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st24;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st24;
	} else
		goto st24;
	goto st16;
tr44:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st25;
tr47:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st25;
tr53:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 595 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st26;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st27;
	} else
		goto st27;
	goto st14;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 37 )
		goto st17;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st24;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st24;
	} else
		goto st24;
	goto st16;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 37 )
		goto tr29;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr51;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr52;
	} else
		goto tr52;
	goto tr28;
tr52:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 647 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr51;
		case 37: goto tr53;
		case 38: goto tr54;
		case 43: goto tr55;
		case 59: goto tr54;
		case 95: goto tr51;
		case 126: goto tr51;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto tr51;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr51;
	} else
		goto tr51;
	goto tr30;
tr48:
#line 34 "ext/query_parser/parse_query.rl"
	{
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
	goto st29;
tr54:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 34 "ext/query_parser/parse_query.rl"
	{
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
	goto st29;
tr66:
#line 52 "ext/query_parser/parse_query.rl"
	{
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
	goto st29;
tr72:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 52 "ext/query_parser/parse_query.rl"
	{
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
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 758 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr56;
		case 37: goto tr57;
		case 43: goto tr58;
		case 95: goto tr56;
		case 126: goto tr56;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr56;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr56;
		} else if ( (*p) >= 64 )
			goto tr56;
	} else
		goto tr56;
	goto st16;
tr41:
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st30;
tr77:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 806 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 37: goto st17;
		case 93: goto st31;
	}
	goto st16;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 37: goto st17;
		case 61: goto st32;
	}
	goto st16;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 33: goto tr61;
		case 37: goto tr62;
		case 43: goto tr63;
		case 95: goto tr61;
		case 126: goto tr61;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr61;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr61;
		} else if ( (*p) >= 64 )
			goto tr61;
	} else
		goto tr61;
	goto st16;
tr61:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st33;
tr63:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st33;
tr67:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st33;
tr69:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st33;
tr73:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 888 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st33;
		case 37: goto tr65;
		case 38: goto tr66;
		case 43: goto tr67;
		case 59: goto tr66;
		case 95: goto st33;
		case 126: goto st33;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st33;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st33;
	} else
		goto st33;
	goto st16;
tr62:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st34;
tr65:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st34;
tr71:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 938 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st35;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st36;
	} else
		goto st36;
	goto st14;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 37 )
		goto st17;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st33;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st33;
	} else
		goto st33;
	goto st16;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 37 )
		goto tr29;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr69;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr70;
	} else
		goto tr70;
	goto tr28;
tr70:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 990 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr69;
		case 37: goto tr71;
		case 38: goto tr72;
		case 43: goto tr73;
		case 59: goto tr72;
		case 95: goto tr69;
		case 126: goto tr69;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto tr69;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr69;
	} else
		goto tr69;
	goto tr30;
tr36:
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 1019 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr35;
		case 37: goto tr74;
		case 43: goto tr75;
		case 61: goto tr76;
		case 91: goto tr77;
		case 95: goto tr35;
		case 126: goto tr35;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr35;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr35;
		} else if ( (*p) >= 64 )
			goto tr35;
	} else
		goto tr35;
	goto tr30;
tr10:
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 1055 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto tr14;
		case 37: goto tr15;
		case 43: goto tr16;
		case 95: goto tr14;
		case 126: goto tr14;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr14;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr14;
		} else if ( (*p) >= 64 )
			goto tr14;
	} else
		goto tr14;
	goto st1;
tr14:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st39;
tr16:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st39;
tr80:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 1103 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st39;
		case 37: goto tr78;
		case 38: goto tr79;
		case 43: goto tr80;
		case 59: goto tr79;
		case 95: goto st39;
		case 126: goto st39;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st39;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st39;
	} else
		goto st39;
	goto st1;
tr15:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st7;
tr78:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 1143 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st8;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st27;
	} else
		goto st27;
	goto st14;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 37 )
		goto st2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st39;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st39;
	} else
		goto st39;
	goto st1;
tr11:
#line 26 "ext/query_parser/parse_query.rl"
	{
        current_key = rb_enc_str_new(buffer, p - buffer, encoding);

        if (encoded) current_key = rb_funcall(unescaper, rb_intern("call"), 1, current_key);

        current_key = rb_obj_freeze(current_key);
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 1184 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 37: goto st2;
		case 93: goto st10;
	}
	goto st1;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 37: goto st2;
		case 61: goto st11;
	}
	goto st1;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 33: goto tr22;
		case 37: goto tr23;
		case 43: goto tr24;
		case 95: goto tr22;
		case 126: goto tr22;
	}
	if ( (*p) < 39 ) {
		if ( 35 <= (*p) && (*p) <= 36 )
			goto tr22;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr22;
		} else if ( (*p) >= 64 )
			goto tr22;
	} else
		goto tr22;
	goto st1;
tr22:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
	goto st40;
tr24:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st40;
tr83:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st40;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
#line 1250 "ext/query_parser/parse_query.c"
	switch( (*p) ) {
		case 33: goto st40;
		case 37: goto tr81;
		case 38: goto tr82;
		case 43: goto tr83;
		case 59: goto tr82;
		case 95: goto st40;
		case 126: goto st40;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 58 )
			goto st40;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st40;
	} else
		goto st40;
	goto st1;
tr23:
#line 13 "ext/query_parser/parse_query.rl"
	{
        encoded = 0;
        buffer = p;
    }
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st12;
tr81:
#line 18 "ext/query_parser/parse_query.rl"
	{
        encoded = 1;
    }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1290 "ext/query_parser/parse_query.c"
	if ( (*p) == 37 )
		goto st18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st13;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st36;
	} else
		goto st36;
	goto st14;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 37 )
		goto st2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st40;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st40;
	} else
		goto st40;
	goto st1;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
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
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 14: 
	case 15: 
	case 18: 
	case 19: 
	case 27: 
	case 36: 
	case 38: 
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
	break;
	case 24: 
	case 39: 
#line 34 "ext/query_parser/parse_query.rl"
	{
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
	break;
	case 33: 
	case 40: 
#line 52 "ext/query_parser/parse_query.rl"
	{
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
	break;
	case 28: 
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 34 "ext/query_parser/parse_query.rl"
	{
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
	break;
	case 37: 
#line 22 "ext/query_parser/parse_query.rl"
	{
        rb_raise(rb_eArgError, "invalid encoding");
    }
#line 52 "ext/query_parser/parse_query.rl"
	{
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
	break;
#line 1466 "ext/query_parser/parse_query.c"
	}
	}

	}

#line 106 "ext/query_parser/parse_query.rl"


    return rb_funcall(parameters, rb_intern("to_h"), 0);
}

