// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <string.h>

#include <ploy/builtins.h>
#include <ploy/printer.h>

void
printer(struct object *object)
{
	if (!object) {
		return;
	}

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
		printer_list(object);
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
printer_list(struct object *list)
{
	putchar('(');

	while (list && list->type != OBJECT_NIL) {
		if (list->type != OBJECT_LIST) {
			printf(" . ");
			printer(list);
			break;
		}

		if (Car(list) && Car(list)->type == OBJECT_NIL) {
			break;
		}

		printer(Car(list));

		if (Cdr(list) && Car(Cdr(list)) && Car(Cdr(list))->type != OBJECT_NIL) {
			putchar(' ');
		}

		list = Cdr(list);
	}

	putchar(')');
}
