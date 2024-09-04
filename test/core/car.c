#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyCar(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyCar(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *car = PloyCar(PloyCons(PloyNumber(42), PloyCons(PloyString("wew"), PloyNil)));
	assert(car != NULL);
	assert(car->type == PloyNUMBER);
	assert(car->number == 42);

	return EXIT_SUCCESS;
}
