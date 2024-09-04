#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <ploy.h>

int
main(void)
{
	Ploy *null = PloyCdr(NULL);
	assert(null != NULL);
	assert(null->type == PloyERROR);

	Ploy *nil = PloyCdr(PloyNil);
	assert(nil != NULL);
	assert(nil->type == PloyERROR);

	Ploy *cdr = PloyCdr(PloyCons(PloyNumber(42), PloyCons(PloyString("wew"), PloyNil)));
	assert(cdr != NULL);
	assert(cdr->type == PloyLIST);

	Ploy *cadr = PloyCar(cdr);
	assert(cadr != NULL);
	assert(cadr->type == PloySTRING);
	assert(strcmp(cadr->string, "wew") == 0);

	return EXIT_SUCCESS;
}
