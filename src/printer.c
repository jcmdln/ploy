// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <ploy/core.h>

void print_list(Object const *list);

void
printer(Object const *object)
{
	if (!object) return;

	switch (object->type) {
	case TYPE_NIL:
		printf("nil");
		break;
	case TYPE_BOOLEAN:
		if (object->boolean)
			printf("true");
		else
			printf("false");
		break;
	case TYPE_ERROR:
		printf("error: %s\n", object->string);
		break;
	// case TYPE_LAMBDA:
	// 	printf("lambda");
	// 	break;
	case TYPE_LIST:
		print_list(object);
		break;
	case TYPE_NUMBER:
		printf("%ld", object->number);
		break;
	case TYPE_STRING:
		printf("\"%s\"", object->string);
		break;
	case TYPE_SYMBOL:
		printf("%s", object->string);
		break;
	}
}

void
print_list(Object const *list)
{
	putchar('(');

	while (list->type != TYPE_NIL) {
		Object const *const car = Car(list);
		if (car->type == TYPE_NIL) break;
		printer(car);

		Object const *const cdr = Cdr(list);
		if (cdr->type == TYPE_NIL) break;
		if (Car(cdr)->type != TYPE_NIL || Cdr(cdr)->type != TYPE_NIL) putchar(' ');
		list = Cdr(list);
	}

	putchar(')');
}
