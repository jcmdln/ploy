// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>

int
main(void)
{
	Object const *null = Reverse(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Reverse(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_NIL);

	Object const *list = Reverse(Read("42 \"wew\""));
	assert(list != NULL);
	assert(list->type == TYPE_LIST);

	Object const *car = Car(list);
	assert(car != NULL);
	assert(car->type == TYPE_STRING);

	Object const *cdr = Cdr(list);
	assert(cdr != NULL);
	assert(cdr->type == TYPE_LIST);

	Object const *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == TYPE_NUMBER);

	Object const *cddr = Cdr(cdr);
	assert(cddr != NULL);
	assert(cddr->type == TYPE_NIL);

	return EXIT_SUCCESS;
}
