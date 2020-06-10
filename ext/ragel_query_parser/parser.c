
#line 1 "ext/ragel_query_parser/parser.rl"
/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"


#line 14 "ext/ragel_query_parser/parser.rl"



#line 18 "ext/ragel_query_parser/parser.c"
static const int parser_start = 1;
static const int parser_first_final = 6;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 17 "ext/ragel_query_parser/parser.rl"

static VALUE parse(int argc, VALUE* argv, VALUE self) {
    VALUE query_string, separator, unescaper;
    rb_scan_args(argc, argv, "11&", &query_string, &separator, &unescaper);

    //%% write exec;
    return Qnil;
}

static VALUE parser_initialize(VALUE self) {
    int cs = 0;
    
#line 39 "ext/ragel_query_parser/parser.c"
	{
	cs = parser_start;
	}

#line 29 "ext/ragel_query_parser/parser.rl"
}

void Init_parser(VALUE rb_mRagelQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mRagelQueryParser, "Parser", rb_cObject);

    rb_define_method(rb_cParser, "initialize", parser_initialize, 0);
    rb_define_method(rb_cParser, "parse", parse, -1);
}
