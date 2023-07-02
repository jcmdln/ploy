// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/token.h>

Token *
token_init(TokenType type, size_t index, char const *const data)
{
	Token *const token = GC_MALLOC(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = data;
	return token;
}

Token *
token_append(Token *const tokens, Token *const token)
{
	if (!tokens) return token;
	if (!tokens->next) {
		tokens->next = token;
		tokens->tail = tokens->next;
		return tokens;
	}

	Token *const tail = tokens->tail;
	tail->next = token;
	tokens->tail = tail->next;
	return tokens;
}
