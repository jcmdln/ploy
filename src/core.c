// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/printer.h>
#include <ploy/reader.h>

const struct object *
Append(const struct object *list, const struct object *object)
{
	if (!list || !list->list) {
		return Cons(object, &Nil);
	}

	if (!list->list->tail) {
		const struct object *head = list;
		const struct object *cdr = Cdr(list);
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

const struct object *
Car(const struct object *object)
{
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->car;
}

const struct object *
Cdr(const struct object *object)
{
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->cdr;
}

const struct object *
Cons(const struct object *car, const struct object *cdr)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

const struct object *
Define(const struct object *env, const struct object *symbol, const struct object *value)
{
	const struct object *object = Cons(symbol, value);
	if (object->type == OBJECT_ERROR) {
		return object;
	}

	return Append(env, object);
}

const struct object *
Error(const char *error)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_ERROR;
	object->atom = error;
	return object;
}

const struct object *
Eval(const struct object *object)
{
	return object;
}

const struct object *
Lambda(const struct object *env, const struct object *args, const struct object *body)
{
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LAMBDA;
	object->lambda = GC_MALLOC(sizeof(*object->lambda));
	object->lambda->env = env;
	object->lambda->args = args;
	object->lambda->body = body;
	return object;
}

const struct object *
Print(const struct object *object)
{
	if (object) {
		printer(object);
		putchar('\n');
	}
	return object;
}

const struct object *
Read(const char *input)
{
	return reader(input);
}

const struct object *
Reverse(const struct object *object)
{
	const struct object *reversed = Cons(&Nil, &Nil);
	while (object && object->type == OBJECT_LIST && Car(object)) {
		reversed = Cons(reversed, Car(object));
		if (!Cdr(object)) {
			break;
		}
		object = Cdr(object);
	}
	return reversed;
}
