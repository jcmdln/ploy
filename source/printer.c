#include <stdio.h>

#include <ploy/core.h>

void print_list(Object *list);

void
printer(Object *object)
{
	if (!object) return;

	switch (object->type) {
	case NIL:
		printf("nil");
		break;
	case BOOLEAN:
		if (object->boolean)
			printf("true");
		else
			printf("false");
		break;
	case ERROR:
		printf("error: %s\n", object->string);
		break;
	// case LAMBDA:
	// 	printf("lambda");
	// 	break;
	case LIST:
		print_list(object);
		break;
	case I64:
		printf("%ld", object->i64);
		break;
	case STRING:
		printf("\"%s\"", object->string);
		break;
	case SYMBOL:
		printf("%s", object->string);
		break;
	}
}

void
print_list(Object *list)
{
	putchar('(');

	while (list->type != NIL) {
		Object *car = Car(list);
		if (car->type == NIL) break;
		printer(car);

		Object *cdr = Cdr(list);
		if (cdr->type == NIL) break;
		if (Car(cdr)->type != NIL || Cdr(cdr)->type != NIL) putchar(' ');
		list = Cdr(list);
	}

	putchar(')');
}
