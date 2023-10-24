#include <gc/gc.h>

#include <ploy/core.h>
#include <ploy/math.h>

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
		if (car->type != I64) return Error("Add: car not of I64");

		int64_t c = car->i64;
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

	int64_t result = Car(object)->i64;
	object = Cdr(object);

	while (object->type == LIST) {
		Object *car = Car(object);
		if (car->type == NIL) break;
		if (car->type != I64) return Error("Subtract: car not of I64");

		int64_t c = car->i64;
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
	if (car->type != I64) return Error("Multiply: car not of I64");

	int64_t result = car->i64;
	object = Cdr(object);
	while (object->type == LIST) {
		car = Car(object);
		if (car->type == NIL) break;
		result *= car->i64;
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
	if (car->type != I64) return Error("Divide: car not of I64");

	int64_t result = car->i64;
	object = Cdr(object);
	while (object->type == LIST) {
		car = Car(object);
		if (car->type == NIL) break;
		result /= car->i64;
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
