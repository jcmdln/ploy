#include <stdio.h>

#include <gc/gc.h>

#include <ploy.h>

Ploy *
PloyApply(Ploy *object)
{
	if (!object) return PloyError("Apply: object is NULL");

	return PloyError("Apply: Not implemented");
}

Ploy *
PloyAppend(Ploy *target, Ploy *object)
{
	if (!object) return PloyError("Append: object is NULL");
	if (!target || target->type == PloyNIL) return PloyCons(object, PloyNil);

	if (target->type != PloyLIST) target = PloyCons(target, PloyNil);

	Ploy *head = target;
	Ploy *cdr = PloyCdr(head);
	while (cdr->type == PloyLIST) {
		head = cdr;
		cdr = PloyCdr(head);
	}

	if (cdr->type != PloyNIL) return PloyError("Append: cdr->type not of NIL");

	head->list->next = PloyCons(object, PloyNil);
	return target;
}

Ploy *
PloyCar(Ploy *object)
{
	if (!object) return PloyError("Car: object is NULL");
	if (object->type != PloyLIST) return PloyError("Car: object is not of type LIST");

	return object->list->element;
}

Ploy *
PloyCdr(Ploy *object)
{
	if (!object) return PloyError("Cdr: object is NULL");
	if (object->type != PloyLIST) return PloyError("Cdr: object is not of type LIST");

	return object->list->next;
}

Ploy *
PloyCons(Ploy *car, Ploy *cdr)
{
	if (!car) return PloyError("Cons: car is NULL");
	if (!cdr) return PloyError("Cons: cdr is NULL");

	Ploy *new = GC_MALLOC(sizeof(*new));
	new->type = PloyLIST;
	new->list = GC_MALLOC(sizeof(*(new->list)));
	new->list->element = car;
	new->list->next = cdr;
	return new;
}

Ploy *
PloyDefine(Ploy *env, Ploy *args, Ploy *body)
{
	if (!env) return PloyError("Define: env is NULL");
	if (!args) return PloyError("Define: args is NULL");
	if (!body) return PloyError("Define: body is NULL");

	return PloyError("Define: Not implemented");
}

Ploy *
PloyError(char const *error)
{
	if (!error) error = "Error: str is NULL";

	Ploy *new = GC_MALLOC(sizeof(*new));
	new->type = PloyERROR;
	new->error = error;
	return new;
}

Ploy *
PloyNumber(int64_t number)
{
	if (number < INT64_MIN) return PloyError("Number: i64 < INT64_MIN");
	if (number > INT64_MAX) return PloyError("Number: i64 > INT64_MAX");

	Ploy *new = GC_MALLOC(sizeof(*new));
	new->type = PloyNUMBER;
	new->number = number;
	return new;
}

Ploy *
PloyPrint(Ploy *object)
{
	if (!object) return PloyError("Print: object is NULL");

	Ploy *head = object;
	Ploy *queue = PloyNil;

	do {
		while (object) {
			switch (object->type) { // clang-format off
			case PloyNIL:     printf("nil"); break;
			case PloyBOOLEAN: printf(object->boolean ? "true" : "false"); break;
			case PloyERROR:   printf("error: %s\n", object->error); break;
			case PloyLAMBDA:  printf("lambda"); break;
			case PloyNUMBER:  printf("%ld", object->number); break;
			case PloySTRING:  printf("\"%s\"", object->string); break;
			case PloySYMBOL:  printf("%s", object->symbol); break;
			case PloyLIST: {
				Ploy *tail = PloyCdr(object);
				if (tail->type == PloyLIST) queue = PloyCons(tail, queue);
				object = PloyCar(object);
				if (object->type == PloyNIL) { putchar(')'); break; }
				if (object->type == PloyLIST) putchar('(');
				continue;
			}
			default: return PloyError("Print: unknown object->type");
			} // clang-format on
			break;
		}

		if (object->type == PloyERROR) return object;
		if (queue->type == PloyNIL) break;
		object = PloyCar(queue);
		queue = PloyCdr(queue);

		// TODO: jcmdln: Audit when spaces are inserted
		if (object->type != PloyNIL && PloyCdr(object)->type != PloyNIL) putchar(' ');
		if (PloyCar(object)->type != PloyNIL && PloyCdr(object)->type == PloyNIL) putchar(' ');
	} while (queue);

	return head;
}

// TODO: jcmdln: non-recursive `Reverse`
Ploy *
PloyReverse(Ploy *object)
{
	if (!object) return PloyError("Reverse: object is NULL");
	if (object->type != PloyLIST) return object;

	Ploy *reversed = PloyNil;
	while (object->type == PloyLIST) {
		Ploy *car = PloyCar(object);
		reversed = (car->type == PloyLIST) ? PloyCons(PloyReverse(car), reversed) :
		                                     PloyCons(car, reversed);
		object = PloyCdr(object);
	}
	return reversed;
}

Ploy *
PloyString(char const *string)
{
	if (!string) return PloyError("String: string is null");

	Ploy *new = GC_MALLOC(sizeof(*new));
	new->type = PloySTRING;
	new->string = string;
	return new;
}
