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

	Object const *overflow = Add(Cons(Number(INT64_MAX), Cons(Number(1), &NIL)));
	assert(overflow != NULL);
	assert(overflow->type == TYPE_ERROR);

	Object const *underflow = Add(Cons(Number(INT64_MIN), Cons(Number(-1), &NIL)));
	assert(underflow != NULL);
	assert(underflow->type == TYPE_ERROR);

	Object const *add = Add(Cons(Number(30), Cons(Number(10), Cons(Number(2), &NIL))));
	assert(add != NULL);
	assert(add->type == TYPE_NUMBER);
	assert(add->number == 42);

	return EXIT_SUCCESS;
}
