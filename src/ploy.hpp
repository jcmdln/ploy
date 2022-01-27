// SPDX-License-Identifier: ISC

#pragma once

#include <cstdint>

struct Object;

struct Lambda {
	struct Object *env;
	struct Object *args;
	struct Object *body;
};

struct List {
	struct Object *car;
	struct Object *cdr;
};

struct Object {
	enum class Type {
		Nil = 0,
		Boolean,
		Error,
		Keyword,
		Lambda,
		List,
		Number,
		String,
		Symbol,
		Type,
	} type;

	union {
		bool boolean;
		char *error;
		char *keyword;
		struct Lambda *lambda;
		struct List *list;
		std::int32_t number;
		char *string;
		char *symbol;
	};
};

static Object Nil = { .type = Object::Type::Nil };
static Object True = { Object::Type::Boolean, { .boolean = true } };
static Object False = { Object::Type::Boolean, { .boolean = false } };

Object *fn_add(Object *);		    // '+'
Object *fn_apply(Object *);		    // 'apply'
Object *fn_as(Object *);		    // 'as'
Object *fn_car(Object *);		    // 'car'
Object *fn_cdr(Object *);		    // 'cdr'
Object *fn_concat(Object *);		    // 'concat'
Object *fn_cons(Object *);		    // 'cons'
Object *fn_divide(Object *);		    // '/'
Object *fn_equal(Object *);		    // '='
Object *fn_eval(Object *);		    // 'eval'
Object *fn_exponent(Object *);		    // '^'
Object *fn_fn(Object *);		    // 'fn'
Object *fn_greater_than(Object *);	    // '>'
Object *fn_greater_than_or_equal(Object *); // '>='
Object *fn_if(Object *);		    // 'if'
Object *fn_is(Object *);		    // 'is'
Object *fn_less_than(Object *);		    // '<'
Object *fn_less_than_or_equal(Object *);    // '<='
void fn_let(Object *, char *, void *);	    // 'let'
Object *fn_macro(Object *);		    // 'macro'
Object *fn_match(Object *);		    // 'match'
Object *fn_modulo(Object *);		    // '%'
Object *fn_multiply(Object *);		    // '*'
Object *fn_not(Object *);		    // 'not'
void fn_print(Object *);		    // 'print'
void fn_printf(char *, Object *);	    // 'printf'
Object *fn_quote(Object *);		    // 'quote', '\''
Object *fn_read(Object *);		    // 'read'
Object *fn_subtract(Object *);		    // '-'
Object *fn_typeof(Object *);		    // 'typeof'

Object *object_new(Object::Type);
Object *object_new_error(char *);
Object *object_new_keyword(char *);
Object *object_new_lambda(Object *, Object *, Object *);
Object *object_new_list(Object *, Object *);
Object *object_new_number(std::int32_t);
Object *object_new_string(char *);
Object *object_new_symbol(char *);
char *object_typename(Object::Type);

void printer(Object *);

Object *reader(char **);
Object *read_keyword(char **);
Object *read_list(char **);
Object *read_number(char **);
Object *read_quote(char **);
Object *read_string(char **);
Object *read_symbol(char **);

void runtime_init(void);
