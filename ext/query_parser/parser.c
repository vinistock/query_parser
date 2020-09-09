/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

#include "parser.h"
#include "parse_query.h"
#include "parse_nested.h"

static VALUE rb_mEncoding;
static VALUE utf_8;
static VALUE rb_cParams;
static VALUE rb_eParameterTypeError;

static VALUE make_params(VALUE self) {
    return rb_funcall(rb_iv_get(self, "@params_class"),
                      rb_intern("new"),
                      1,
                      rb_iv_get(self, "@key_space_limit"));
}

static VALUE parser_initialize(VALUE self, VALUE params_class, VALUE key_space_limit, VALUE param_depth_limit) {
    rb_iv_set(self, "@params_class", params_class);
    rb_iv_set(self, "@key_space_limit", key_space_limit);
    rb_iv_set(self, "@param_depth_limit", param_depth_limit);
    return self;
}

static char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

static VALUE unescape(VALUE self, VALUE string) {
    char *str = RSTRING_PTR(string);
    char *pstr = str, *buf = malloc(strlen(str) + 1), *pbuf = buf;
    VALUE decoded_url;

    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                pstr += 2;
            }
        } else if (*pstr == '+') {
            *pbuf++ = ' ';
        } else {
            *pbuf++ = *pstr;
        }

        pstr++;
    }

    *pbuf = '\0';
    decoded_url = rb_str_new_cstr(buf);
    free(buf);
    return rb_funcall(decoded_url, rb_intern("force_encoding"), 1, utf_8);
}

static VALUE make_default(VALUE self, VALUE key_space_limit, VALUE param_depth_limit) {
    return rb_funcall(self, rb_intern("new"), 3, rb_cParams, key_space_limit, param_depth_limit);
}

static VALUE new_space_limit(VALUE self, VALUE key_space_limit) {
    return rb_funcall(rb_obj_class(self),
                      rb_intern("new"),
                      3,
                      rb_iv_get(self, "@params_class"),
                      key_space_limit,
                      rb_iv_get(self, "@param_depth_limit"));
}

static VALUE new_depth_limit(VALUE self, VALUE param_depth_limit) {
    return rb_funcall(rb_obj_class(self),
                      rb_intern("new"),
                      3,
                      rb_iv_get(self, "@params_class"),
                      rb_iv_get(self, "@key_space_limit"),
                      param_depth_limit);
}

static VALUE check_types(RB_BLOCK_CALL_FUNC_ARGLIST(args, self)) {
    VALUE h = rb_ary_entry(args, 0);
    VALUE part = rb_ary_entry(args, 1);

    if (RSTRING_LEN(part) == 0) {
        rb_funcall(rb_current_receiver(), rb_intern("next"), 1, h);
    }

    if (!(RTEST(rb_obj_is_kind_of(h, rb_iv_get(self, "@params_class"))) && RTEST(rb_hash_aref(h, part)))) {
        return Qfalse;
    }

    return rb_hash_aref(h, part);
}

static VALUE params_hash_has_key(VALUE self, VALUE hash, VALUE key) {
    VALUE regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("\\[\\]")));
    if (RTEST(rb_funcall(regex, rb_intern("match?"), 1, key))) return Qfalse;

    VALUE split_regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("[\\[\\]]+")));
    VALUE args[1];
    args[0] = hash;

    rb_block_call(rb_funcall(key, rb_intern("split"), 1, split_regex), rb_intern("inject"), 1, args, check_types, self);
    return Qtrue;
}

static VALUE normalize_params(VALUE self, VALUE params, VALUE name, VALUE value, VALUE depth) {
    if (NUM2INT(depth) <= 0) rb_raise(rb_eRangeError, "depth must be greater than zero");

    VALUE regex = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("\\A[\\[\\]]*([^\\[\\]]+)\\]*")));
    VALUE regex_2 = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("^\\[\\]\\[([^\\[\\]]+)\\]$")));
    VALUE regex_3 = rb_funcall(rb_cRegexp, rb_intern("new"), 1, rb_obj_freeze(rb_str_new_cstr("^\\[\\](.+)$")));
    VALUE match_data = rb_funcall(regex, rb_intern("match"), 1, name);
    VALUE k = rb_funcall(match_data, rb_intern("[]"), 1, INT2NUM(0));
    VALUE after = rb_funcall(match_data, rb_intern("post_match"), 0);
    VALUE entry = Qnil, array_entry = Qnil;

    if (NIL_P(k)) k = rb_obj_freeze(rb_str_new_cstr(""));
    if (NIL_P(after)) after = rb_obj_freeze(rb_str_new_cstr(""));

    if (RSTRING_LEN(k) == 0) {
        if (!NIL_P(value) && strcmp(RSTRING_PTR(name), "[]") == 0) {
            rb_funcall(value, rb_intern("to_ary"), 0);
        } else {
            return Qnil;
        }
    }

    if (strcmp(RSTRING_PTR(after), "") == 0) {
        rb_funcall(params, rb_intern("[]="), 2, k, value);
    } else if (strcmp(RSTRING_PTR(after), "[") == 0) {
        rb_funcall(params, rb_intern("[]="), 2, name, value);
    } else if (strcmp(RSTRING_PTR(after), "[]") == 0) {
        if (NIL_P(entry = rb_funcall(params, rb_intern("[]"), 1, k))) {
            rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_new());
        }

        if (!RTEST(rb_obj_is_kind_of(entry, rb_cArray))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Array (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_push(entry, value));
    } else if (RTEST(match_data = rb_funcall(regex_2, rb_intern("match"), 1, after)) || RTEST(match_data = rb_funcall(regex_3, rb_intern("match"), 1, after))) {
        VALUE child_key = rb_funcall(match_data, rb_intern("[]"), 1, INT2NUM(0));

        if (NIL_P(entry = rb_funcall(params, rb_intern("[]"), 1, k))) rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_new());

        if (!RTEST(rb_obj_is_kind_of(entry, rb_cArray))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Array (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        if (RTEST(rb_obj_is_kind_of(array_entry = rb_ary_entry(entry, RARRAY_LEN(entry) - 1), rb_iv_get(self, "@params_class"))) && !RTEST(params_hash_has_key(self, array_entry, child_key))) {
            normalize_params(self, array_entry, child_key, value, INT2NUM(NUM2INT(depth) - 1));
        } else {
            rb_funcall(params, rb_intern("[]="), 2, k, rb_ary_push(entry, normalize_params(self, make_params(self), child_key, value, INT2NUM(NUM2INT(depth) - 1))));
        }
    } else {
        if (NIL_P(entry = rb_funcall(params, rb_intern("[]"), 1, k))) rb_funcall(params, rb_intern("[]="), 2, k, make_params(self));

        if (!RTEST(rb_obj_is_kind_of(entry, rb_iv_get(self, "@params_class")))) {
            rb_raise(rb_eParameterTypeError,
                     "expected Hash (got %s) for param `%s'",
                     rb_obj_classname(entry),
                     RSTRING_PTR(rb_funcall(k, rb_intern("to_s"), 0)));
        }

        rb_funcall(params, rb_intern("[]="), 2, k, normalize_params(self, entry, after, value, INT2NUM(NUM2INT(depth) - 1)));
    }

    return params;
}

void Init_parser(VALUE rb_mQueryParser) {
    VALUE rb_cParser = rb_define_class_under(rb_mQueryParser, "Parser", rb_cObject);
    rb_eParameterTypeError = rb_define_class_under(rb_cParser, "ParameterTypeError", rb_eTypeError);

    rb_cParams = rb_const_get(rb_mQueryParser, rb_intern("Params"));
    rb_mEncoding = rb_const_get(rb_cObject, rb_intern("Encoding"));
    utf_8 = rb_const_get(rb_mEncoding, rb_intern("UTF_8"));

    rb_funcall(rb_cParser, rb_intern("attr_reader"), 2, ID2SYM(rb_intern("key_space_limit")), ID2SYM(rb_intern("param_depth_limit")));

    rb_define_method(rb_cParser, "initialize", parser_initialize, 3);
    rb_define_method(rb_cParser, "new_space_limit", new_space_limit, 1);
    rb_define_method(rb_cParser, "new_depth_limit", new_depth_limit, 1);
    rb_define_method(rb_cParser, "make_params", make_params, 0);
    rb_define_method(rb_cParser, "normalize_params", normalize_params, 4);

    rb_define_method(rb_cParser, "parse_query", parse_query, -1);
    rb_define_method(rb_cParser, "parse_nested_query", parse_nested_query, -1);

    rb_define_singleton_method(rb_cParser, "unescape", unescape, 1);
    rb_define_singleton_method(rb_cParser, "make_default", make_default, 2);
}
