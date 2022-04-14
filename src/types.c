// SPDX-License-Identifier: ISC

#include "types.h"

#include <gc.h>

char *
object_typename(enum object_t type)
{
	switch (type) {
	case nil_t:
		return "nil";
	case boolean_t:
		return "boolean";
	case error_t:
		return "error";
	case keyword_t:
		return "keyword";
	case lambda_t:
		return "lambda";
	case list_t:
		return "list";
	case number_t:
		return "number";
	case string_t:
		return "string";
	case symbol_t:
		return "symbol";
	}

	return "unknown";
}

struct object *
object_new(enum object_t type)
{
	struct object *obj = (struct object *)GC_MALLOC(sizeof(*obj));

	obj->type = type;

	return obj;
}

struct object *
object_new_boolean(bool boolean)
{
	struct object *obj = object_new(boolean_t);

	obj->boolean = boolean;

	return obj;
}

struct object *
object_new_error(char *error)
{
	struct object *obj = object_new(error_t);

	obj->error = error;

	return obj;
}

struct object *
object_new_keyword(char *keyword)
{
	struct object *obj = object_new(keyword_t);

	obj->keyword = keyword;

	return obj;
}

struct object *
object_new_lambda(struct object *env, struct object *args, struct object *body)
{
	struct object *obj = object_new(lambda_t);

	obj->lambda = (struct lambda *)GC_MALLOC(sizeof(*obj->lambda));
	obj->lambda->env = env;
	obj->lambda->args = args;
	obj->lambda->body = body;

	return obj;
}

struct object *
object_new_list(struct object *car, struct object *cdr)
{
	struct object *obj = object_new(list_t);

	obj->list = (struct list *)GC_MALLOC(sizeof(*obj->list));
	obj->list->car = car;
	obj->list->cdr = cdr;

	return obj;
}

struct object *
object_new_number(int64_t number)
{
	struct object *obj = object_new(number_t);
	obj->number = number;
	return obj;
}

struct object *
object_new_string(char *string)
{
	struct object *obj = object_new(string_t);

	obj->string = string;

	return obj;
}

struct object *
object_new_symbol(char *symbol)
{
	struct object *obj = object_new(symbol_t);

	obj->symbol = symbol;

	return obj;
}
