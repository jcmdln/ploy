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
	Object const *null = Multiply(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Multiply(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	Object const *multiply = Multiply(Read("2 3 7"));
	assert(multiply != NULL);
	assert(multiply->type == TYPE_NUMBER);
	assert(multiply->number == 42);

	Object const *multiply_alt = Multiply(Cons(Number(2), Cons(Number(3), Cons(Number(7), &NIL))));
	assert(multiply_alt != NULL);
	assert(multiply_alt->type == TYPE_NUMBER);
	assert(multiply->number == multiply_alt->number);

	return EXIT_SUCCESS;
}
