#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyAdd(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyAdd(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *add = PloyAdd(
		PloyCons(PloyNumber(30), PloyCons(PloyNumber(10), PloyCons(PloyNumber(2), PloyNil))));
	assert(add != NULL);
	assert(add->type == PloyNUMBER);
	assert(add->number == 42);

	return EXIT_SUCCESS;
}
