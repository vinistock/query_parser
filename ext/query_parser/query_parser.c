#include "query_parser.h"
#include "params.h"
#include "parser.h"

void Init_query_parser(void) {
  VALUE rb_mQueryParser = rb_define_module("QueryParser");

  Init_params(rb_mQueryParser);
  Init_parser(rb_mQueryParser);
}
