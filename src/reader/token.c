// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/token.h>

struct token *
new_token(enum token_type type, size_t index, char const *const data)
{
	struct token *const token = GC_MALLOC(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = data;
	return token;
}

struct token *
token_append(struct token *const tokens, struct token *const token)
{
	if (!tokens) {
		return token;
	}

	if (!tokens->next) {
		tokens->next = token;
		tokens->tail = tokens->next;
		return tokens;
	}

	struct token *const tail = tokens->tail;
	tail->next = token;
	tokens->tail = tail->next;
	return tokens;
}
