#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>

int
main(void)
{
	Object *null = Cdr(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Cdr(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object *cdr = Cdr(Cons(Number(42), Cons(String("wew"), Nil)));
	assert(cdr != NULL);
	assert(cdr->type == LIST);

	Object *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == STRING);

	return EXIT_SUCCESS;
}
