#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Multiply(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Multiply(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object *multiply = Multiply(Cons(Number(2), Cons(Number(3), Cons(Number(7), Nil))));
	assert(multiply != NULL);
	assert(multiply->type == NUMBER);
	assert(multiply->number == 42);

	return EXIT_SUCCESS;
}
