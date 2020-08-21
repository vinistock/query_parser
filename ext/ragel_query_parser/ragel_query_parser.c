#include "ragel_query_parser.h"
#include "params.h"
#include "parser.h"

VALUE rb_mRagelQueryParser;

void Init_ragel_query_parser(void) {
  rb_mRagelQueryParser = rb_define_module("RagelQueryParser");

  Init_params(rb_mRagelQueryParser);
  Init_parser(rb_mRagelQueryParser);
}
