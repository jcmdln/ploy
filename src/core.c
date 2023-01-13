// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/printer.h>
#include <ploy/reader.h>

Object *
Append(Object *list, Object *object)
{
	if (!object) return Error("Append: object is NULL");
	if (!list) return Cons(object, &Nil);

	Object *head = list;
	while (head && Car(head) && Cdr(head) && Cdr(head)->type == OBJECT_LIST)
		head = Cdr(head);

	head->list->cdr = Cons(object, &Nil);
	return list;
}

Object *
Car(Object *object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != OBJECT_LIST) return Error("Cdr: object is not of type LIST");
	return object->list->car;
}

Object *
Cdr(Object *object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != OBJECT_LIST) return Error("Cdr: object is not of type LIST");
	return object->list->cdr;
}

Object *
Cons(Object *car, Object *cdr)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

Object *
Error(const char *error)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_ERROR;
	object->error = error;
	return object;
}

Object *
Eval(Object *object)
{
	return object;
}

Object *
Lambda(Object *env, Object *args, Object *body)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LAMBDA;
	object->lambda = GC_MALLOC(sizeof(*object->lambda));
	object->lambda->env = env;
	object->lambda->args = args;
	object->lambda->body = body;
	return object;
}

Object *
Print(Object *object)
{
	Object *head = object;
	if (head) {
		printer(head);
		putchar('\n');
	}
	return object;
}

Object *
Read(const char *input)
{
	return reader(input);
}

Object *
Reverse(Object *object)
{
	if (!object) return Error("Reverse: object is NULL");
	Object *head = object;
	Object *reversed = Cons(NULL, NULL);
	while (head && head->type == OBJECT_LIST && Car(head)) {
		reversed = Cons(reversed, Car(head));
		if (!Cdr(head)) break;
		head = Cdr(head);
	}
	return reversed;
}
