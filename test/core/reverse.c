#include <assert.h>
#include <stdlib.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyReverse(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyReverse(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyNIL);

	Ploy *list = PloyReverse(PloyCons(PloyNumber(42), PloyCons(PloyString("wew"), PloyNil)));
	assert(list != NULL);
	assert(list->type == PloyLIST);

	Ploy *car = PloyCar(list);
	assert(car != NULL);
	assert(car->type == PloySTRING);

	Ploy *cdr = PloyCdr(list);
	assert(cdr != NULL);
	assert(cdr->type == PloyLIST);

	Ploy *cadr = PloyCar(cdr);
	assert(cadr != NULL);
	assert(cadr->type == PloyNUMBER);

	Ploy *cddr = PloyCdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == PloyNIL);

	return EXIT_SUCCESS;
}
