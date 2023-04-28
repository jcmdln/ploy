// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/core.h>
#include <ploy/reader.h>
#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>
#include <ploy/type.h>

const struct object *read_list_delimiters(Token *tokens);

const struct object *
reader(const char *input)
{
	if (!input) {
		return Error("reader: input is NULL");
	}

	Token *tokens = lexer(input);
	if (!tokens) {
		return Error("reader: tokens is NULL");
	}
	if (tokens->type == TOKEN_ERROR) {
		return Error(tokens->data);
	}

	const struct object *err = read_list_delimiters(tokens);
	if (err->type == OBJECT_ERROR) {
		return err;
	}

	const struct object *parsed = parser(tokens);
	return parsed;
}

const struct object *
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

	if (balanced < 0) {
		return Error("read_list_delimiters: missing open parenthesis");
	}
	if (balanced > 0) {
		return Error("read_list_delimiters: missing closing parenthesis");
	}

	return &Nil;
}
