#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloySubtract(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloySubtract(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *subtract = PloySubtract(PloyCons(PloyNumber(100), PloyCons(PloyNumber(58), PloyNil)));
	assert(subtract != NULL);
	assert(subtract->type == PloyNUMBER);
	assert(subtract->number == 42);

	return EXIT_SUCCESS;
}
