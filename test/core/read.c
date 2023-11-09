#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Read(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Read("");
	assert(nil != NULL);
	assert(nil->type == NIL);

	Object *list = Car(Read("(42 \"wew\")"));
	assert(list != NULL);
	assert(list->type == LIST);

	Object *car = Car(list);
	assert(car != NULL);
	assert(car->type == NUMBER);
	assert(car->number == 42);

	Object *cdr = Cdr(list);
	assert(cdr != NULL);
	assert(cdr->type == LIST);

	Object *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == STRING);
	assert(strcmp(cadr->string, "wew") == 0);

	Object *cddr = Cdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == NIL);

	return EXIT_SUCCESS;
}
