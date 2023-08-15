// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/core.h>

void printer(Object const *object);
Object const *reader(char const *input);

Object const *
Append(Object const *target, Object const *const object)
{
	if (!object) return Error("Append: object is NULL");
	if (!target || target->type == TYPE_NIL) return Cons(object, &NIL);
	if (target->type != TYPE_LIST) target = Cons(target, &NIL);

	Object const *head = target;
	Object const *cdr = Cdr(head);
	while (cdr->type == TYPE_LIST) {
		head = cdr;
		cdr = Cdr(head);
	}

	if (cdr->type != TYPE_NIL) return Error("Append: cdr->type not of TYPE_NIL");
	head->list->cdr = Cons(object, &NIL);
	return target;
}

Object const *
Car(Object const *const object)
{
	if (!object) return Error("Car: object is NULL");
	if (object->type != TYPE_LIST) return Error("Car: object is not of type LIST");

	return object->list->car;
}

Object const *
Cdr(Object const *const object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != TYPE_LIST) return Error("Cdr: object is not of type LIST");

	return object->list->cdr;
}

Object const *
Cons(Object const *const car, Object const *const cdr)
{
	if (!car) return Error("Cons: car is NULL");
	if (!cdr) return Error("Cons: cdr is NULL");

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = TYPE_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

Object const *
Eval(Object const *const object)
{
	if (!object) return Error("Eval: object is NULL");

	return object;
}

Object const *
Print(Object const *const object)
{
	if (!object) return Error("Print: object is NULL");

	printer(object);
	return object;
}

Object const *
Read(char const *const input)
{
	if (!input) return Error("Read: input is NULL");

	return reader(input);
}

Object const *
Reverse(Object const *const object)
{
	if (!object) return Error("Reverse: object is NULL");
	if (object->type != TYPE_LIST) return object;

	Object const *head = object;
	Object const *reversed = &NIL;
	while (head->type == TYPE_LIST) {
		Object const *car = Car(head);
		reversed = (car->type == TYPE_LIST) ? Cons(Reverse(car), reversed) : Cons(car, reversed);
		head = Cdr(head);
	}
	return reversed;
}
