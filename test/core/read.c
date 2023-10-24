#include <assert.h>
#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/core.h>

int
main(void)
{
	Object *null = Read(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Read("\0");
	assert(nil != NULL);
	assert(nil->type == NIL);

	Object *list = Cons(Number(42), Cons(String("wew"), Nil));
	assert(list != NULL);
	assert(list->type == LIST);

	Object *car = Car(list);
	assert(car != NULL);
	assert(car->type == I64);

	Object *cdr = Cdr(list);
	assert(cdr != NULL);
	assert(cdr->type == LIST);

	Object *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == STRING);

	Object *cddr = Cdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == NIL);

	return EXIT_SUCCESS;
}
