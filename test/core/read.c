#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyRead(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyRead("");
	assert(nil != NULL);
	assert(nil->type == PloyNIL);

	Ploy *list = PloyCar(PloyRead("(42 \"wew\")"));
	assert(list != NULL);
	assert(list->type == PloyLIST);

	Ploy *car = PloyCar(list);
	assert(car != NULL);
	assert(car->type == PloyNUMBER);
	assert(car->number == 42);

	Ploy *cdr = PloyCdr(list);
	assert(cdr != NULL);
	assert(cdr->type == PloyLIST);

	Ploy *cadr = PloyCar(cdr);
	assert(cadr != NULL);
	assert(cadr->type == PloySTRING);
	assert(strcmp(cadr->string, "wew") == 0);

	Ploy *cddr = PloyCdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == PloyLIST);

	Ploy *caddr = PloyCar(cddr);
	assert(caddr != NULL);
	assert(caddr->type == PloyNIL);

	return EXIT_SUCCESS;
}
