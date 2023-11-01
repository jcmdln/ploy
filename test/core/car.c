#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Object *null = Car(NULL);
	assert(null != NULL);
	assert(null->type == ERROR);

	Object *nil = Car(Nil);
	assert(nil != NULL);
	assert(nil->type == ERROR);

	Object *car = Car(Cons(Number(42), Cons(String("wew"), Nil)));
	assert(car != NULL);
	assert(car->type == NUMBER);
	assert(car->number == 42);

	return EXIT_SUCCESS;
}
