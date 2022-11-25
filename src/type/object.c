// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ploy/gc.h>
#include <ploy/type/object.h>

struct object *
object_new(enum object_type type)
{
	struct object *object = (struct object *)gc_alloc(sizeof(*object));
	object->type = type;
	return object;
}

struct object *
object_boolean(bool boolean)
{
	struct object *object = object_new(OBJECT_BOOLEAN);
	object->boolean = boolean;
	return object;
}

struct object *
object_error(const char *error)
{
	struct object *object = object_new(OBJECT_ERROR);
	object->error = error;
	return object;
}

struct object *
object_keyword(const char *keyword)
{
	struct object *object = object_new(OBJECT_KEYWORD);
	object->keyword = keyword;
	return object;
}

struct object *
object_lambda(struct lambda *lambda)
{
	struct object *object = object_new(OBJECT_LAMBDA);
	object->lambda = lambda;
	return object;
}

struct object *
object_list(struct list *list)
{
	struct object *object = object_new(OBJECT_LIST);
	if (!list) {
		object->list = list_new(object_nil(), object_nil());
	} else {
		object->list = list;
	}
	return object;
}

struct object *
object_nil(void)
{
	return object_new(OBJECT_NIL);
}

struct object *
object_number(int64_t number)
{
	struct object *object = object_new(OBJECT_NUMBER);
	object->number = number;
	return object;
}

struct object *
object_string(const char *string)
{
	struct object *object = object_new(OBJECT_STRING);
	object->string = string;
	return object;
}

struct object *
object_symbol(const char *symbol)
{
	struct object *object = object_new(OBJECT_SYMBOL);
	object->symbol = symbol;
	return object;
}
