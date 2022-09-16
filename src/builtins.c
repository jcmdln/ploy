// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <ploy/builtins.h>
#include <ploy/printer.h>
#include <ploy/reader/reader.h>

struct object *
Append(struct object *list, struct object *object)
{
	if (!object) {
		return object_error("Append: object is NULL");
	}

	if (!list) {
		return object;
	}

	if (list->type != OBJECT_LIST) {
		return object_list(list_new(list, object_list(list_new(object, object_nil()))));
	}

	return object_list(list_append(list->list, object));
}

struct object *
Car(struct object *list)
{
	if (!list || list->type != OBJECT_LIST) {
		return NULL;
	}

	return list->list->element;
}

struct object *
Cdr(struct object *list)
{
	if (!list || list->type != OBJECT_LIST) {
		return NULL;
	}

	return list->list->next;
}

struct object *
Cons(struct object *car, struct object *cdr)
{
	return object_list(list_new(car, cdr));
}

struct object *
Eval(struct object *object)
{
	return object;
}

struct object *
Print(struct object *object)
{
	struct object *head = object;
	if (head) {
		printer(head);
		putchar('\n');
	}

	return object;
}

struct object *
Read(char *input)
{
	return reader(input);
}

struct object *
Reverse(struct object *object)
{
	struct list *list = list_reverse(object->list);
	if (!list) {
		return object_error("Reverse: list_reverse returned NULL");
	}

	return object_list(list);
}
