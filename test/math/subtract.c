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
	Object const *null = Subtract(NULL);
	assert(null != NULL);
	assert(null->type == TYPE_ERROR);

	Object const *nil = Subtract(&NIL);
	assert(nil != NULL);
	assert(nil->type == TYPE_ERROR);

	// (- 1 2 3 4 32)
	Object const *subtract = Subtract(
		Cons(Number(1), Cons(Number(2), Cons(Number(3), Cons(Number(4), Cons(Number(32), &NIL))))));
	assert(subtract != NULL);
	assert(subtract->type == TYPE_NUMBER);
	assert(subtract->number == -42);

	return EXIT_SUCCESS;
}
