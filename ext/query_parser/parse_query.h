#ifndef QP_PARSE_QUERY_H
#define QP_PARSE_QUERY_H 1

#include <ruby.h>
#include <string.h>
#include <ruby/encoding.h>
#include <ctype.h>

extern VALUE parse_query(int argc, VALUE* argv, VALUE self);

#endif
