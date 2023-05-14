// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/reader.h>
#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>

struct object const *read_list_delimiters(struct token const *tokens);

struct object const *
reader(char const *const input)
{
	if (!input) {
		return Error("reader: input is NULL");
	}

	struct token const *const tokens = lexer(input);
	if (!tokens) {
		return Error("reader: tokens is NULL");
	}
	if (tokens->type == TOKEN_ERROR) {
		return Error(tokens->data);
	}

	struct object const *const err = read_list_delimiters(tokens);
	if (err->type == OBJECT_ERROR) {
		return err;
	}

	return parser(tokens);
}

struct object const *
read_list_delimiters(struct token const *const tokens)
{
	struct token const *head = tokens;
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
