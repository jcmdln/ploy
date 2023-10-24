#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy/core.h>
#include <ploy/evaluator.h>
#include <ploy/math.h>

Object *
evaluator(Object *object)
{
	if (!object) return Error("evaluator: object is NULL");

	// switch (object->type) {
	// case NIL:
	// case BOOLEAN:
	// case ERROR:
	// case LIST:
	// case I64:
	// case STRING:
	// case SYMBOL:
	// 	break;
	// }

	// Object *head = object;
	//
	// while (head->type != NIL) {
	// 	Object *car = Car(head);
	// 	Object *cdr = Cdr(head);
	//
	// 	if (car->type == SYMBOL && strcmp(car->symbol, "+") == 0) return Add(cdr);
	//
	// 	if (car->type == LIST) {
	// 		Object *caar = Car(Car(head));
	// 		Object *cadr = Cdr(Car(head));
	//
	// 		if (caar->type == SYMBOL && strcmp(caar->symbol, "+") == 0) return Add(cadr);
	// 	}
	//
	// 	head = Cdr(head);
	// }

	return object;
}
