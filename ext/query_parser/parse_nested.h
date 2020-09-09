#ifndef QP_PARSE_NESTED_H
#define QP_PARSE_NESTED_H 1

#include <ruby.h>
#include <string.h>
#include <ruby/encoding.h>
#include <ctype.h>

extern VALUE parse_nested_query(int argc, VALUE* argv, VALUE self);

#endif
