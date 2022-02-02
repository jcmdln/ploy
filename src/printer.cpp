// SPDX-License-Identifier: ISC

extern "C" {
#include <stdio.h>
}

#include "printer.hpp"

void
printer(Object *obj)
{
	switch (obj->type()) {
	case Object::Type::Nil:
		printf("wnil");
		break;

	case Object::Type::Boolean:
		printf((((Boolean *)obj)->value ? "true" : "false"));
		break;

	case Object::Type::Error:
		printf("%s", ((Error *)obj)->value);
		break;

	case Object::Type::Keyword:
		printf(":%s", ((Keyword *)obj)->value);
		break;

	case Object::Type::Lambda:
		printf("<lambda>");
		break;

	case Object::Type::List:
		obj = print_list((List *)obj);
		break;

	case Object::Type::Number:
		printf("%d", ((Number *)obj)->value);
		break;

	case Object::Type::String:
		printf("\"%s\"", ((String *)obj)->value);
		break;

	case Object::Type::Symbol:
		printf("%s", ((Symbol *)obj)->value);
		break;

	default:
		fprintf(stderr, "error: printer: unknown type '%s'",
		    object_typename(obj->type()));
		break;
	}
}

Object *
print_list(Object *obj)
{
	printf("(");

	while (obj && obj->type() != Object::Type::Nil) {
		if (obj->type() == Object::Type::List) {
			if (!(((List *)obj)->car)) {
				fputs("error: car is NULL\n", stderr);
				exit(1);
			}

			printer(((List *)obj)->car);
			if (obj->type() != Object::Type::List) {
				printf(" . ");
				printer(obj);
				break;
			}
		}

		Object *cdr = ((List *)obj)->cdr;
		if (cdr && ((List *)cdr)->type() != Object::Type::Nil) {
			printf(" ");
		}

		obj = cdr;
	}

	printf(")");

	return obj;
}
