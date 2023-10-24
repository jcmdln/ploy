#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>
#include <ploy/math.h>

int
main(void)
{
	Object *null = Divide(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Divide(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object const *divide = Divide(Cons(Number(42), Cons(Number(7), Cons(Number(3), Nil))));
	assert(divide != NULL);
	assert(divide->type == I64);
	assert(divide->i64 == 2);

	return EXIT_SUCCESS;
}
