// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <string.h>

#include <ploy/ploy.h>
#include <ploy/printer.h>

void print_list(Object const *list);

void
printer(Object const *const object)
{
	if (!object) return;

	switch (object->type) {
	case OBJECT_NIL:
		printf("nil");
		break;
	case OBJECT_BOOLEAN:
		printf(object->boolean ? "true" : "false");
		break;
	case OBJECT_ERROR:
		printf("error: %s\n", object->error);
		break;
	case OBJECT_KEYWORD:
		printf(":%s", object->keyword);
		break;
	case OBJECT_LAMBDA:
		printf("<lambda>");
		break;
	case OBJECT_LIST:
		print_list(object);
		break;
	case OBJECT_NUMBER:
		printf("%ld", object->number);
		break;
	case OBJECT_STRING:
		printf("\"%s\"", object->string);
		break;
	case OBJECT_SYMBOL:
		printf("%s", object->symbol);
		break;
	}
}

void
print_list(Object const *list)
{
	putchar('(');

	while (list && list->type != OBJECT_NIL) {
		if (list->type != OBJECT_LIST) {
			printf(" . ");
			printer(list);
			break;
		}

		Object const *const car = Car(list);
		Object const *const cdr = Cdr(list);

		if (car->type == OBJECT_NIL && cdr->type == OBJECT_NIL) {
			list = cdr;
			continue;
		}

		printer(car);

		if (car->type != OBJECT_NIL && cdr->type != OBJECT_NIL)
			if (Car(cdr)->type != OBJECT_NIL || Cdr(cdr)->type != OBJECT_NIL) putchar(' ');

		list = cdr;
	}

	putchar(')');
}
