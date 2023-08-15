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
	Object const *null = Divide(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Divide(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	// (/ 42 7 3)
	Object const *divide = Divide(Cons(Number(42), Cons(Number(7), Cons(Number(3), &NIL))));
	assert(divide != NULL);
	assert(divide->type == TYPE_NUMBER);
	assert(divide->number == 2);

	return EXIT_SUCCESS;
}