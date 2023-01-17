// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/reader.h>
#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>

Object *read_list_delimiters(Token *tokens);

Object *
reader(const char *input)
{
	Token *tokens = lexer(input);
	if (tokens->type == TOKEN_ERROR) return Error(tokens->data);

	Object *err = read_list_delimiters(tokens);
	if (err->type == OBJECT_ERROR) return err;

	Object *parsed = parser(tokens);
	GC_FREE((void *)tokens); // FIXME: reader: freeing `Tokens *` violates `-Wcast-qual`
	return parsed;
}

Object *
read_list_delimiters(Token *tokens)
{
	Token *head = tokens;
	int32_t balanced = 0;

	while (head && head->data) {
		switch (*head->data) {
		case '(':
			++balanced;
			break;
		case ')':
			--balanced;
			break;
		}
		head = head->next;
	}

	if (balanced < 0) return Error("read_list_delimiters: missing open parenthesis");
	if (balanced > 0) return Error("read_list_delimiters: missing closing parenthesis");

	return &Nil;
}
