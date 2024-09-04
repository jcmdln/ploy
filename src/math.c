#include <gc/gc.h>

#include <ploy.h>

//
// Arithmetic
//

Ploy *
PloyAdd(Ploy *object)
{
	if (!object) return PloyError("Add: object is NULL");
	if (object->type != PloyLIST) return PloyError("Add: object not of LIST");

	Ploy *car = PloyCar(object);
	if (car->type != PloyNUMBER) return PloyError("Add: car not of NUMBER");
	int64_t result = car->number;
	object = PloyCdr(object);

	while (object->type == PloyLIST) {
		Ploy *car = PloyCar(object);
		if (car->type == PloyNIL) break;
		if (car->type != PloyNUMBER) return PloyError("Add: car not of NUMBER");

		result += car->number;
		object = PloyCdr(object);
	}

	return PloyNumber(result);
}

Ploy *
PloySubtract(Ploy *object)
{
	if (!object) return PloyError("Subtract: object is NULL");
	if (object->type != PloyLIST) return PloyError("Subtract: object not of LIST");

	Ploy *car = PloyCar(object);
	if (car->type != PloyNUMBER) return PloyError("Subtract: car not of NUMBER");
	int64_t result = car->number;
	object = PloyCdr(object);

	while (object->type == PloyLIST) {
		Ploy *car = PloyCar(object);
		if (car->type == PloyNIL) break;
		if (car->type != PloyNUMBER) return PloyError("Subtract: car not of NUMBER");

		result -= car->number;
		object = PloyCdr(object);
	}

	return PloyNumber(result);
}

Ploy *
PloyMultiply(Ploy *object)
{
	if (!object) return PloyError("Multiply: object is NULL");
	if (object->type != PloyLIST) return PloyError("Multiply: object not of LIST");

	Ploy *car = PloyCar(object);
	if (car->type != PloyNUMBER) return PloyError("Multiply: car not of NUMBER");
	int64_t result = car->number;
	object = PloyCdr(object);

	while (object->type == PloyLIST) {
		car = PloyCar(object);
		if (car->type == PloyNIL) break;
		result *= car->number;
		object = PloyCdr(object);
	}

	return PloyNumber(result);
}

Ploy *
PloyDivide(Ploy *object)
{
	if (!object) return PloyError("Divide: object is NULL");
	if (object->type != PloyLIST) return PloyError("Divide: object not of LIST");

	Ploy *car = PloyCar(object);
	if (car->type != PloyNUMBER) return PloyError("Divide: car not of NUMBER");
	int64_t result = car->number;
	object = PloyCdr(object);

	while (object->type == PloyLIST) {
		car = PloyCar(object);
		if (car->type == PloyNIL) break;
		result /= car->number;
		object = PloyCdr(object);
	}

	return PloyNumber(result);
}

// Ploy *
// PloyExponent(Ploy *object)
// {
// 	if (!object) return PloyError("Exponent: object is NULL");
// 	if (object->type != PloyLIST) return PloyError("Exponent: object not of LIST");
// 	return PloyNumber(0);
// }

// PloyLog(Ploy *object)
// {
// 	if (!object) return PloyError("Log: object is NULL");
// 	if (object->type != PloyLIST) return PloyError("Log: object not of LIST");
// 	return PloyNumber(0);
// }

// Ploy *
// PloyModulo(Ploy *object)
// {
// 	if (!object) return PloyError("Modulo: object is NULL");
// 	if (object->type != PloyLIST) return PloyError("Modulo: object not of LIST");
// 	return PloyNumber(0);
// }

// Ploy *
// PloyNthRoot(Ploy *object)
// {
// 	if (!object) return PloyError("NthRoot: object is NULL");
// 	if (object->type != PloyLIST) return PloyError("Root: object not of LIST");
// 	return PloyNumber(0);
// }
