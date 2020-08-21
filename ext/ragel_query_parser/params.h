#ifndef RQP_PARAMS_H
#define RQP_PARAMS_H 1

#include <ruby.h>

void Init_params(VALUE rb_mRagelQueryParser);
VALUE params_set(VALUE self, VALUE key, VALUE value);

#endif
