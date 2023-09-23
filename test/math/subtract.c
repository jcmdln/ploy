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

	Object const *overflow = Subtract(Cons(Number(INT64_MAX), Cons(Number(-1), &NIL)));
	assert(overflow != NULL);
	assert(overflow->type == TYPE_ERROR);

	Object const *underflow = Subtract(Cons(Number(INT64_MIN), Cons(Number(1), &NIL)));
	assert(underflow != NULL);
	assert(underflow->type == TYPE_ERROR);

	Object const *subtract = Subtract(Read("100 58"));
	assert(subtract != NULL);
	assert(subtract->type == TYPE_NUMBER);
	assert(subtract->number == 42);

	Object const *subtract_alt = Subtract(Cons(Number(100), Cons(Number(58), &NIL)));
	assert(subtract_alt != NULL);
	assert(subtract_alt->type == TYPE_NUMBER);
	assert(subtract->number == subtract_alt->number);

	return EXIT_SUCCESS;
}
