// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>

int
main(void)
{
	Object const *null = Cons(NULL, NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Cons(&NIL, &NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_LIST);

	Object const *cons = Cons(Number(42), &NIL);
	assert(cons != NULL);
	assert(cons->type == TYPE_LIST);

	Object const *car = Car(cons);
	assert(car != NULL);
	assert(car->type == TYPE_NUMBER);

	Object const *cdr = Cdr(cons);
	assert(cdr != NULL);
	assert(cdr->type == TYPE_NIL);

	return EXIT_SUCCESS;
}
