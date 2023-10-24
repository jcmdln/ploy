#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>
#include <ploy/math.h>

int
main(void)
{
	Object *null = Subtract(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Subtract(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object *overflow = Subtract(Cons(Number(INT64_MAX), Cons(Number(-1), Nil)));
	assert(overflow != NULL);
	assert(overflow->type == ERROR);

	Object *underflow = Subtract(Cons(Number(INT64_MIN), Cons(Number(1), Nil)));
	assert(underflow != NULL);
	assert(underflow->type == ERROR);

	Object *subtract = Subtract(Cons(Number(100), Cons(Number(58), Nil)));
	assert(subtract != NULL);
	assert(subtract->type == I64);
	assert(subtract->i64 == 42);

	return EXIT_SUCCESS;
}
