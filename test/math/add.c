#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>
#include <ploy/math.h>

int
main(void)
{
	Object *null = Add(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Add(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object const *overflow = Add(Cons(Number(INT64_MAX), Cons(Number(1), Nil)));
	assert(overflow != NULL);
	assert(overflow->type == ERROR);

	Object const *underflow = Add(Cons(Number(INT64_MIN), Cons(Number(-1), Nil)));
	assert(underflow != NULL);
	assert(underflow->type == ERROR);

	Object const *add = Add(Cons(Number(30), Cons(Number(10), Cons(Number(2), Nil))));
	assert(add != NULL);
	assert(add->type == I64);
	assert(add->i64 == 42);

	return EXIT_SUCCESS;
}
