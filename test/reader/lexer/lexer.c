// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/reader/lexer.h>

int
main(void)
{
	struct token *token = lexer(NULL);

	assert(token != NULL);
	assert(token->type == TOKEN_ERROR);

	return EXIT_SUCCESS;
}
