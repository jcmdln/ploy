// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>

int
main(void)
{
	Object const *null = Car(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Car(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	Object const *car = Car(Cons(Number(42), Cons(String("wew"), &NIL)));
	assert(car != NULL);
	assert(car->type == TYPE_NUMBER);

	return EXIT_SUCCESS;
}
