#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/core.h>
#include <ploy/evaluator.h>
#include <ploy/printer.h>
#include <ploy/reader.h>

Object *
Append(Object *target, Object *object)
{
	if (!object) return Error("Append: object is NULL");
	if (!target || target->type == NIL) return Cons(object, Nil);
	if (target->type != LIST) target = Cons(target, Nil);

	Object *head = target;
	Object *cdr = Cdr(head);
	while (cdr->type == LIST) {
		head = cdr;
		cdr = Cdr(head);
	}

	if (cdr->type != NIL) return Error("Append: cdr->type not of NIL");

	head->cdr = Cons(object, Nil);
	return target;
}

Object *
Car(Object *object)
{
	if (!object) return Error("Car: object is NULL");
	if (object->type != LIST) return Error("Car: object is not of type LIST");
	return object->car;
}

Object *
Cdr(Object *object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != LIST) return Error("Cdr: object is not of type LIST");
	return object->cdr;
}

Object *
Cons(Object *car, Object *cdr)
{
	if (!car) return Error("Cons: car is NULL");
	if (!cdr) return Error("Cons: cdr is NULL");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = LIST;
	new->car = car;
	new->cdr = cdr;
	return new;
}

Object *
Error(char *error)
{
	if (!error) return Error("Error: error is NULL");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = ERROR;
	new->string = error;
	return new;
}

Object *
Eval(Object *object)
{
	if (!object) return Error("Eval: object is NULL");
	return evaluator(object);
}

Object *
Number(int64_t i64)
{
	Object *new = GC_MALLOC(sizeof(*new));
	new->type = I64;
	new->i64 = i64;
	return new;
}

Object *
Print(Object *object)
{
	if (!object) return Error("Print: object is NULL");
	printer(object);
	return object;
}

Object *
Read(char *input)
{
	if (!input) return Error("Read: input is NULL");
	return reader(input);
}

Object *
Reverse(Object *object)
{
	if (!object) return Error("Reverse: object is NULL");
	if (object->type != LIST) return object;

	Object *head = object;
	Object *reversed = Nil;
	while (head->type == LIST) {
		Object *car = Car(head);
		if (car->type == LIST)
			reversed = Cons(Reverse(car), reversed);
		else
			reversed = Cons(car, reversed);
		head = Cdr(head);
	}
	return reversed;
}

Object *
String(char *string)
{
	Object *new = GC_MALLOC(sizeof(*new));
	new->type = STRING;
	new->string = string;
	return new;
}

Object *
Symbol(char *symbol)
{
	Object *new = GC_MALLOC(sizeof(*new));
	new->type = SYMBOL;
	new->string = symbol;
	return new;
}
