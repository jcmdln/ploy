// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ploy/ploy.h>
#include <ploy/reader.h>
#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>

Object *read_list_delimiters(Token *tokens);

Object *
reader(const char *input)
{
	if (!input) return Error("reader: input is NULL");

	Token *tokens = lexer(input);
	if (!tokens) return Error("reader: tokens is NULL");
	if (tokens->type == TOKEN_ERROR) return Error(tokens->data);

#ifdef PLOY_DEBUG
	token_print(tokens);
#endif // PLOY_DEBUG

	Object *object = read_list_delimiters(tokens);
	if (object && object->type == OBJECT_ERROR) return object;

	return parser(tokens);
}

Object *
read_list_delimiters(Token *tokens)
{
	if (!tokens) return Error("read_list_delimiters: tokens is NULL");

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
