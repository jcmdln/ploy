#include <gc/gc.h>

#include <ploy.h>

//
// Arithmetic
//

Object *
Add(Object *object)
{
	if (!object) return Error("Add: object is NULL");
	if (object->type != LIST) return Error("Add: object not of LIST");

	int64_t result = 0;
	while (object->type == LIST) {
		Object *car = Car(object);
		if (car->type == NIL) break;
		if (car->type != NUMBER) return Error("Add: car not of NUMBER");

		int64_t c = car->number;
		if ((c > 0 && result > (INT64_MAX - c)) || (c < 0 && result < (INT64_MIN - c)))
			return Error("Add: overflow");

		result += c;
		object = Cdr(object);
	}

	return Number(result);
}

Object *
Subtract(Object *object)
{
	if (!object) return Error("Subtract: object is NULL");
	if (object->type != LIST) return Error("Subtract: object not of LIST");

	int64_t result = Car(object)->number;
	object = Cdr(object);

	while (object->type == LIST) {
		Object *car = Car(object);
		if (car->type == NIL) break;
		if (car->type != NUMBER) return Error("Subtract: car not of NUMBER");

		int64_t c = car->number;
		if ((c > 0 && result < (INT64_MIN + c)) || (c < 0 && result > (INT64_MAX + c)))
			return Error("Subtract: overflow");

		result -= c;
		object = Cdr(object);
	}

	return Number(result);
}

Object *
Multiply(Object *object)
{
	if (!object) return Error("Multiply: object is NULL");
	if (object->type != LIST) return Error("Multiply: object not of LIST");

	Object *car = Car(object);
	if (!car) return Error("Multiply: car is NULL");
	if (car->type != NUMBER) return Error("Multiply: car not of NUMBER");

	int64_t result = car->number;
	object = Cdr(object);
	while (object->type == LIST) {
		car = Car(object);
		if (car->type == NIL) break;
		result *= car->number;
		object = Cdr(object);
	}

	return Number(result);
}

Object *
Divide(Object *object)
{
	if (!object) return Error("Divide: object is NULL");
	if (object->type != LIST) return Error("Divide: object not of LIST");

	Object *car = Car(object);
	if (!car) return Error("Divide: car is NULL");
	if (car->type != NUMBER) return Error("Divide: car not of NUMBER");

	int64_t result = car->number;
	object = Cdr(object);
	while (object->type == LIST) {
		car = Car(object);
		if (car->type == NIL) break;
		result /= car->number;
		object = Cdr(object);
	}

	return Number(result);
}

// Object *
// Exponent(Object *object)
// {
// 	if (!object) return Error("Exponent: object is NULL");
// 	if (object->type != LIST) return Error("Exponent: object not of LIST");
// 	return Number(0);
// }

// Log(Object *object)
// {
// 	if (!object) return Error("Log: object is NULL");
// 	if (object->type != LIST) return Error("Log: object not of LIST");
// 	return Number(0);
// }

// Object *
// Modulo(Object *object)
// {
// 	if (!object) return Error("Modulo: object is NULL");
// 	if (object->type != LIST) return Error("Modulo: object not of LIST");
// 	return Number(0);
// }

// Object *
// NthRoot(Object *object)
// {
// 	if (!object) return Error("NthRoot: object is NULL");
// 	if (object->type != LIST) return Error("Root: object not of LIST");
// 	return Number(0);
// }
