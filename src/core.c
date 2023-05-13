// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/printer.h>
#include <ploy/reader.h>

struct object const *
Append(struct object const *const list, struct object const *const object)
{
	if (!list || !list->list) {
		return Cons(object, &Nil);
	}

	if (!list->list->tail) {
		struct object const *head = list;
		struct object const *cdr = Cdr(list);
		while (cdr && cdr->type == OBJECT_LIST) {
			head = cdr;
			cdr = Cdr(head);
		}
		list->list->tail = head;
	}

	list->list->tail->list->cdr = Cons(object, &Nil);
	list->list->tail = list->list->tail->list->cdr;
	return list;
}

struct object const *
Car(struct object const *const object)
{
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->car;
}

struct object const *
Cdr(struct object const *const object)
{
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->cdr;
}

struct object const *
Cons(struct object const *const car, struct object const *const cdr)
{
	struct object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

struct object const *
Define(struct object const *const env, struct object const *const symbol,
	struct object const *const value)
{
	struct object const *const object = Cons(symbol, value);
	if (object->type == OBJECT_ERROR) {
		return object;
	}

	return Append(env, object);
}

struct object const *
Error(char const *error)
{
	struct object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_ERROR;
	object->atom = error;
	return object;
}

struct object const *
Eval(struct object const *const object)
{
	return object;
}

struct object const *
Lambda(struct object const *const env, struct object const *const args,
	struct object const *const body)
{
	struct object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LAMBDA;
	object->lambda = GC_MALLOC(sizeof(*object->lambda));
	object->lambda->env = env;
	object->lambda->args = args;
	object->lambda->body = body;
	return object;
}

struct object const *
Print(struct object const *const object)
{
	if (object) {
		printer(object);
		putchar('\n');
	}
	return object;
}

struct object const *
Read(char const *const input)
{
	return reader(input);
}

struct object const *
Reverse(struct object const *object)
{
	struct object const *reversed = Cons(&Nil, &Nil);
	while (object && object->type == OBJECT_LIST && Car(object)) {
		reversed = Cons(reversed, Car(object));
		if (!Cdr(object)) {
			break;
		}
		object = Cdr(object);
	}
	return reversed;
}
