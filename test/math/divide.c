#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyDivide(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyDivide(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *divide = PloyDivide(
		PloyCons(PloyNumber(42), PloyCons(PloyNumber(7), PloyCons(PloyNumber(3), PloyNil))));
	assert(divide != NULL);
	assert(divide->type == PloyNUMBER);
	assert(divide->number == 2);

	return EXIT_SUCCESS;
}
