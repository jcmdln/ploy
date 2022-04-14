// SPDX-License-Identifier: ISC

#ifndef BUILTINS_H
#pragma once

#include "types.h"

struct object *fn_add(struct object *);			  // '+'
struct object *fn_apply(struct object *);		  // 'apply'
struct object *fn_as(struct object *);			  // 'as'
struct object *fn_car(struct object *);			  // 'car'
struct object *fn_cdr(struct object *);			  // 'cdr'
struct object *fn_concat(struct object *);		  // 'concat'
struct object *fn_cons(struct object *);		  // 'cons'
struct object *fn_divide(struct object *);		  // '/'
struct object *fn_equal(struct object *);		  // '='
struct object *fn_eval(struct object *);		  // 'eval'
struct object *fn_exponent(struct object *);		  // '^'
struct object *fn_fn(struct object *);			  // 'fn'
struct object *fn_greater_than(struct object *);	  // '>'
struct object *fn_greater_than_or_equal(struct object *); // '>='
struct object *fn_if(struct object *);			  // 'if'
struct object *fn_is(struct object *);			  // 'is'
struct object *fn_less_than(struct object *);		  // '<'
struct object *fn_less_than_or_equal(struct object *);	  // '<='
void fn_let(struct object *, char *, void *);		  // 'let'
struct object *fn_macro(struct object *);		  // 'macro'
struct object *fn_match(struct object *);		  // 'match'
struct object *fn_modulo(struct object *);		  // '%'
struct object *fn_multiply(struct object *);		  // '*'
struct object *fn_not(struct object *);			  // 'not'
void fn_print(struct object *);				  // 'print'
void fn_printf(char *, struct object *);		  // 'printf'
struct object *fn_quote(struct object *);		  // 'quote', '\''
struct object *fn_read(struct object *);		  // 'read'
struct object *fn_subtract(struct object *);		  // '-'
struct object *fn_typeof(struct object *);		  // 'typeof'

#endif // BUILTINS_H
