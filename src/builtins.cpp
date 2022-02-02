// SPDX-License-Identifier: ISC

extern "C" {
#include <stdio.h>
#include <stdlib.h>
}

#include "builtins.hpp"

Object *
fn_add(Object *obj)
{
	auto sum{ 0 };

	while (obj && obj->type() != Object::Type::Nil) {
		if (obj->type() != Object::Type::Number) {
			fputs("error: '+': invalid argument(s)", stderr);
			exit(1);
		}

		sum += ((Number *)obj)->value;
		obj = ((List *)obj)->cdr;
	}

	return new Number(sum);
}

Object *
fn_car(Object *obj)
{
	return ((List *)obj)->car;
}

Object *
fn_cdr(Object *obj)
{
	return ((List *)obj)->cdr;
}

Object *
fn_cons(Object *obj)
{
	return new List(fn_car(obj), fn_cdr(fn_car(obj)));
}

Object *
fn_eval(Object *obj)
{
	return obj;
}

Object *
fn_typeof(Object *obj)
{
	return new String(object_typename(obj->type()));
}
