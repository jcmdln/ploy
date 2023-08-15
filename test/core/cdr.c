// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>

int
main(void)
{
	Object const *null = Cdr(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Cdr(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	Object const *cdr = Cdr(Read("42 \"wew\""));
	assert(cdr != NULL);
	assert(cdr->type == TYPE_LIST);

	Object const *cadr = Car(cdr);
	assert(cadr != NULL);
	assert(cadr->type == TYPE_STRING);

	return EXIT_SUCCESS;
}
