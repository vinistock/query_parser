#ifndef QP_PARAMS_H
#define QP_PARAMS_H 1

#include <ruby.h>

void Init_params(VALUE rb_mQueryParser);
VALUE params_set(VALUE self, VALUE key, VALUE value);

#endif
