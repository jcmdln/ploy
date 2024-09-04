#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyMultiply(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyMultiply(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *multiply = PloyMultiply(
		PloyCons(PloyNumber(2), PloyCons(PloyNumber(3), PloyCons(PloyNumber(7), PloyNil))));
	assert(multiply != NULL);
	assert(multiply->type == PloyNUMBER);
	assert(multiply->number == 42);

	return EXIT_SUCCESS;
}
