#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Divide(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Divide(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object *divide = Divide(Cons(Number(42), Cons(Number(7), Cons(Number(3), Nil))));
	assert(divide != NULL);
	assert(divide->type == NUMBER);
	assert(divide->number == 2);

	return EXIT_SUCCESS;
}
