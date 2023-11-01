#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Reverse(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Reverse(Nil);
	assert(nil != NULL);
	assert(nil->type == NIL);

	Object *list = Reverse(Cons(Number(42), Cons(String("wew"), Nil)));
	assert(list != NULL);
	assert(list->type == LIST);

	Object *car = Car(list);
	assert(car != NULL);
	assert(car->type == STRING);

	Object *cdr = Cdr(list);
	assert(cdr != NULL);
	assert(cdr->type == LIST);

	Object *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == NUMBER);

	Object *cddr = Cdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == NIL);

	return EXIT_SUCCESS;
}
