#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Cons(NULL, NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Cons(Nil, Nil);
	assert(nil != NULL);
	assert(nil->type == LIST);

	Object *cons = Cons(Number(42), Nil);
	assert(cons != NULL);
	assert(cons->type == LIST);

	Object *car = Car(cons);
	assert(car != NULL);
	assert(car->type == NUMBER);

	Object *cdr = Cdr(cons);
	assert(cdr != NULL);
	assert(cdr->type == NIL);

	return EXIT_SUCCESS;
}
