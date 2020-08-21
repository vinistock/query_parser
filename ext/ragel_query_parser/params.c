#include "params.h"

static VALUE rb_cParams;

static VALUE params_initialize(VALUE self, VALUE limit) {
    rb_iv_set(self, "@limit", limit);
    rb_iv_set(self, "@size", LONG2NUM(0));
    rb_iv_set(self, "@params", rb_hash_new());
    return self;
}

static VALUE params_access(VALUE self, VALUE key) {
    return rb_hash_aref(rb_iv_get(self, "@params"), key);
}

static VALUE params_has_key(VALUE self, VALUE key) {
    return RTEST(rb_hash_aref(rb_iv_get(self, "@params"), key)) ? Qtrue : Qfalse;
}

VALUE params_set(VALUE self, VALUE key, VALUE value) {
    long size = NUM2LONG(rb_iv_get(self, "@size"));

    if (RTEST(key) && !RTEST(params_has_key(self, key))) {
        size += rb_str_strlen(key);
        rb_iv_set(self, "@size", LONG2NUM(size));
    }

    if (size > NUM2LONG(rb_iv_get(self, "@limit"))) {
        rb_raise(rb_eRangeError, "exceeded available parameter key space");
    }

    return rb_hash_aset(rb_iv_get(self, "@params"), key, value);
}

static VALUE remap_params(RB_BLOCK_CALL_FUNC_ARGLIST(value, args)) {
    if (RTEST(rb_obj_is_kind_of(value, rb_cParams))) {
        return rb_funcall(value, rb_intern("to_h"), 0);
    } else {
        return value;
    }
}

static int process_params(VALUE key, VALUE value, VALUE args) {
    VALUE self = rb_current_receiver();

    if (RTEST(rb_equal(self, value))) {
        rb_hash_aset(rb_iv_get(self, "@params"), key, rb_iv_get(self, "@params"));
    } else if (RTEST(rb_obj_is_kind_of(value, rb_cParams))) {
        rb_hash_aset(rb_iv_get(self, "@params"), key, rb_funcall(value, rb_intern("to_h"), 0));
    } else if (RTEST(rb_obj_is_kind_of(value, rb_cArray))) {
        rb_block_call(value, rb_intern("map!"), 0, NULL, remap_params, Qnil);
    }

    return ST_CONTINUE;
}

static VALUE params_to_hash(VALUE self) {
    VALUE params = rb_iv_get(self, "@params");
    rb_hash_foreach(params, process_params, (VALUE)NULL);
    return params;
}

void Init_params(VALUE rb_mRagelQueryParser) {
    rb_cParams = rb_define_class_under(rb_mRagelQueryParser, "Params", rb_cObject);

    rb_define_method(rb_cParams, "initialize", params_initialize, 1);
    rb_define_method(rb_cParams, "[]", params_access, 1);
    rb_define_method(rb_cParams, "[]=", params_set, 2);
    rb_define_method(rb_cParams, "key?", params_has_key, 1);
    rb_define_method(rb_cParams, "to_h", params_to_hash, 0);

    rb_define_alias(rb_cParams, "to_params_hash", "to_h");
}
