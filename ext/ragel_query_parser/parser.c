
#line 1 "ext/ragel_query_parser/parser.rl"
/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */


#line 12 "ext/ragel_query_parser/parser.rl"



#line 16 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 6;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 15 "ext/ragel_query_parser/parser.rl"

int main() {
    
#line 28 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 18 "ext/ragel_query_parser/parser.rl"
    
#line 35 "ext/ragel_query_parser/parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 98: goto st2;
		case 102: goto st4;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 97 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 114 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 111 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111 )
		goto st6;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 19 "ext/ragel_query_parser/parser.rl"
    return 0;
}
