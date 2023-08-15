// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/core.h>
#include <ploy/math.h>

int
main(void)
{
	Object const *null = Add(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Add(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	// (+ 1 2 3 4 32)
	Object const *add = Add(
		Cons(Number(1), Cons(Number(2), Cons(Number(3), Cons(Number(4), Cons(Number(32), &NIL))))));
	assert(add != NULL);
	assert(add->type == TYPE_NUMBER);
	assert(add->number == 42);

	return EXIT_SUCCESS;
}
