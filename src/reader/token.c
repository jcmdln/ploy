// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/reader/token.h>

struct token *
token_append(struct token *tokens, struct token *token)
{
	if (!tokens) return token;

	struct token *head = tokens;
	while (head && head->next)
		head = head->next;

	head->next = token;
	return tokens;
}

struct token *
new_token(enum token_type type, size_t index, const char *data)
{
	struct token *token = GC_MALLOC(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = GC_MALLOC(sizeof(*token->data));
	token->data = data;
	return token;
}
