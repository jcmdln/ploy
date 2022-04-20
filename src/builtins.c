// SPDX-License-Identifier: ISC

#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"
#include "types.h"

struct object *
fn_add(struct object *obj)
{
	int64_t sum = 0;

	while (obj && obj->type != nil_t) {
		if (obj->type != number_t) {
			fputs("error: '+': invalid argument(s)", stderr);
			exit(1);
		}

		sum += obj->number;
		obj = obj->list->cdr;
	}

	return object_new_number(sum);
}

struct object *
fn_car(struct object *obj)
{
	return obj->list->car;
}

struct object *
fn_cdr(struct object *obj)
{
	return obj->list->cdr;
}

struct object *
fn_cons(struct object *obj)
{
	return object_new_list(list_new(fn_car(obj), fn_cdr(fn_car(obj))));
}

struct object *
fn_eval(struct object *obj)
{
	return obj;
}

struct object *
fn_typeof(struct object *obj)
{
	return object_new_string(object_typename(obj->type));
}
