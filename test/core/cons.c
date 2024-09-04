#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyCons(NULL, NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyCons(PloyNil, PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyLIST);

	Ploy *cons = PloyCons(PloyNumber(42), PloyNil);
	assert(cons != NULL);
	assert(cons->type == PloyLIST);

	Ploy *car = PloyCar(cons);
	assert(car != NULL);
	assert(car->type == PloyNUMBER);

	Ploy *cdr = PloyCdr(cons);
	assert(cdr != NULL);
	assert(cdr->type == PloyNIL);

	return EXIT_SUCCESS;
}
