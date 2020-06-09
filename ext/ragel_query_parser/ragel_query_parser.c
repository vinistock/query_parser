#include "ragel_query_parser.h"

VALUE rb_mRagelQueryParser;

static VALUE parse(VALUE self, VALUE query) {
    return Qnil;
}

void Init_ragel_query_parser(void) {
  rb_mRagelQueryParser = rb_define_module("RagelQueryParser");

  rb_define_singleton_method(rb_mRagelQueryParser, "parse", parse, 1);
}
