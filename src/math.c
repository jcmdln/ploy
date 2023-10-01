// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <gc.h>

#include <ploy/core.h>
#include <ploy/math.h>

Object const *
Add(Object const *object)
{
	if (!object) return Error("Add: object is NULL");
	if (object->type != TYPE_LIST) return Error("Add: object not of TYPE_LIST");

	Object *result = Number(0);
	while (object->type == TYPE_LIST) {
		Object const *car = Car(object);
		if (car->type != TYPE_NUMBER) return Error("Add: car not of TYPE_NUMBER");

		int64_t r = result->number;
		int64_t c = car->number;
		if ((c > 0 && r > (INT64_MAX - c)) || (c < 0 && r < (INT64_MIN - c)))
			return Error("Add: overflow");

		result->number += c;
		object = Cdr(object);
	}

	return result;
}

Object const *
Divide(Object const *object)
{
	if (!object) return Error("Divide: object is NULL");
	if (object->type != TYPE_LIST) return Error("Divide: object not of TYPE_LIST");

	Object const *car = Car(object);
	if (!car) return Error("Divide: car is NULL");
	if (car->type != TYPE_NUMBER) return Error("Divide: car not of TYPE_NUMBER");

	Object *result = Number(car->number);
	object = Cdr(object);
	while (object->type == TYPE_LIST) {
		car = Car(object);
		result->number /= car->number;
		object = Cdr(object);
	}

	return result;
}

Object const *
Exponent(Object const *object)
{
	if (!object) return Error("Exponent: object is NULL");
	if (object->type != TYPE_LIST) return Error("Exponent: object not of TYPE_LIST");

	Object *result = Number(0);

	return result;
}

// Log(Object const *object)
// {
// 	if (!object) return Error("Log: object is NULL");
// 	if (object->type != TYPE_LIST) return Error("Log: object not of TYPE_LIST");
//
// 	Object *result = Number(0);
//
// 	return result;
// }

// Object const *
// Modulo(Object const *object)
// {
// 	if (!object) return Error("Modulo: object is NULL");
// 	if (object->type != TYPE_LIST) return Error("Modulo: object not of TYPE_LIST");
//
// 	Object *result = Number(0);
//
// 	return result;
// }

Object const *
Multiply(Object const *object)
{
	if (!object) return Error("Multiply: object is NULL");
	if (object->type != TYPE_LIST) return Error("Multiply: object not of TYPE_LIST");

	Object const *car = Car(object);
	if (!car) return Error("Multiply: car is NULL");
	if (car->type != TYPE_NUMBER) return Error("Multiply: car not of TYPE_NUMBER");

	Object *result = Number(car->number);
	object = Cdr(object);
	while (object->type == TYPE_LIST) {
		car = Car(object);
		result->number *= car->number;
		object = Cdr(object);
	}

	return result;
}

// Object const *
// NthRoot(Object const *object)
// {
// 	if (!object) return Error("Root: object is NULL");
// 	if (object->type != TYPE_LIST) return Error("Root: object not of TYPE_LIST");
//
// 	Object *result = Number(0);
//
// 	return result;
// }

Object const *
Subtract(Object const *object)
{
	if (!object) return Error("Subtract: object is NULL");
	if (object->type != TYPE_LIST) return Error("Subtract: object not of TYPE_LIST");

	int64_t result = Car(object)->number;
	object = Cdr(object);

	while (object->type == TYPE_LIST) {
		Object const *car = Car(object);
		if (car->type != TYPE_NUMBER) return Error("Subtract: car not of TYPE_NUMBER");

		int64_t c = car->number;
		if ((c > 0 && result < (INT64_MIN + c)) || (c < 0 && result > (INT64_MAX + c)))
			return Error("Subtract: overflow");

		result -= c;
		object = Cdr(object);
	}

	return Number(result);
}
