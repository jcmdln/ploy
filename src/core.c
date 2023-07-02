// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/printer.h>
#include <ploy/reader/reader.h>

Object const *
Append(Object const *const target, Object const *const object)
{
	if (!target || !target->list) return Cons(object, &Nil);

	if (!target->list->tail) {
		Object const *head = target;
		Object const *cdr = Cdr(target);

		while (cdr && cdr->type == OBJECT_LIST) {
			head = cdr;
			cdr = Cdr(head);
		}

		target->list->tail = head;
	}

	target->list->tail->list->cdr = Cons(object, &Nil);
	target->list->tail = target->list->tail->list->cdr;

	return target;
}

Object const *
Car(Object const *const object)
{
	if (!object) return Error("Car: object is NULL");
	if (object->type != OBJECT_LIST) return Error("Car: object is not of type LIST");
	return object->list->car;
}

Object const *
Cdr(Object const *const object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != OBJECT_LIST) return Error("Cdr: object is not of type LIST");
	return object->list->cdr;
}

Object const *
Cons(Object const *const car, Object const *const cdr)
{
	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

Object const *
Define(Object const *const env, Object const *const symbol, Object const *const value)
{
	Object const *const object = Cons(symbol, value);
	if (object->type == OBJECT_ERROR) return object;

	return Append(env, object);
}

Object const *
Error(char const *error)
{
	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_ERROR;
	object->error = error;
	return object;
}

Object const *
Eval(Object const *const object)
{
	return object;
}

Object const *
Lambda(Object const *const env, Object const *const args, Object const *const body)
{
	if (env) {
	}

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LAMBDA;
	object->lambda = GC_MALLOC(sizeof(*object->lambda));
	object->lambda->args = args;
	object->lambda->body = body;
	return object;
}

Object const *
Print(Object const *const object)
{
	if (object) {
		printer(object);
		putchar('\n');
	}
	return object;
}

Object const *
Read(char const *const input)
{
	return reader(input);
}

Object const *
Reverse(Object const *object)
{
	Object const *reversed = Cons(&Nil, &Nil);
	while (object && object->type == OBJECT_LIST && Car(object)) {
		reversed = Cons(reversed, Car(object));
		if (!Cdr(object)) break;
		object = Cdr(object);
	}
	return reversed;
}
