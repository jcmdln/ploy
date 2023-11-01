#include <stdio.h>

#include <gc/gc.h>

#include <ploy.h>

Object *
Apply(Object *object)
{
	if (!object) return Error("Apply: object is NULL");

	return Error("Apply: Not implemented");
}

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

	head->next = Cons(object, Nil);
	return target;
}

Object *
Car(Object *object)
{
	if (!object) return Error("Car: object is NULL");
	if (object->type != LIST) return Error("Car: object is not of type LIST");

	return object->element;
}

Object *
Cdr(Object *object)
{
	if (!object) return Error("Cdr: object is NULL");
	if (object->type != LIST) return Error("Cdr: object is not of type LIST");

	return object->next;
}

Object *
Cons(Object *car, Object *cdr)
{
	if (!car) return Error("Cons: car is NULL");
	if (!cdr) return Error("Cons: cdr is NULL");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = LIST;
	new->element = car;
	new->next = cdr;
	return new;
}

Object *
Define(Object *env, Object *args, Object *body)
{
	if (!env) return Error("Define: env is NULL");
	if (!args) return Error("Define: args is NULL");
	if (!body) return Error("Define: body is NULL");

	return Error("Define: Not implemented");
}

Object *
Error(char const *error)
{
	if (!error) error = "Error: str is NULL";

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = ERROR;
	new->error = error;
	return new;
}

Object *
Number(int64_t number)
{
	if (number < INT64_MIN) return Error("Number: i64 < INT64_MIN");
	if (number > INT64_MAX) return Error("Number: i64 > INT64_MAX");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = NUMBER;
	new->number = number;
	return new;
}

Object *
Print(Object *object)
{
	if (!object) return Error("Print: object is NULL");

	Object *head = object;
	Object *queue = Nil;

	do {
		while (object) {
			switch (object->type) { // clang-format off
			case NIL:     printf("nil"); break;
			case BOOLEAN: printf(object->boolean ? "true" : "false"); break;
			case ERROR:   printf("error: %s\n", object->error); break;
			case LAMBDA:  printf("lambda"); break;
			case NUMBER:  printf("%ld", object->number); break;
			case STRING:  printf("\"%s\"", object->string); break;
			case SYMBOL:  printf("%s", object->symbol); break;
			case LIST: {
				Object *tail = Cdr(object);
				if (tail->type == LIST) queue = Cons(tail, queue);
				object = Car(object);
				if (object->type == NIL) { putchar(')'); break; }
				if (object->type == LIST) putchar('(');
				continue;
			}
			default: return Error("Print: unknown object->type");
			} // clang-format on
			break;
		}

		if (object->type == ERROR) return object;
		if (queue->type == NIL) break;
		object = Car(queue);
		queue = Cdr(queue);

		// TODO(jcmdln): Audit when spaces are inserted
		if (object->type != NIL && Cdr(object)->type != NIL) putchar(' ');
		if (Car(object)->type != NIL && Cdr(object)->type == NIL) putchar(' ');
	} while (queue);

	return head;
}

// TODO(jcmdln): non-recursive `Reverse`
Object *
Reverse(Object *object)
{
	if (!object) return Error("Reverse: object is NULL");
	if (object->type != LIST) return object;

	Object *reversed = Nil;
	while (object->type == LIST) {
		Object *car = Car(object);
		reversed = (car->type == LIST) ? Cons(Reverse(car), reversed) : Cons(car, reversed);
		object = Cdr(object);
	}
	return reversed;
}

Object *
String(char const *string)
{
	if (!string) return Error("String: string is null");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = STRING;
	new->string = string;
	return new;
}
