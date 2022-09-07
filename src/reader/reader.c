// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <string.h>

#include <ploy/reader.h>

struct object *
reader(char *input)
{
	if (!input) {
		fputs("error: reader: input is NULL", stderr);
		return NULL;
	}

	struct token *tokens = lexer(input);
	if (!tokens) {
		return NULL;
	}

	if (!read_list_delimiters(tokens)) {
		return NULL;
	}

	return parser(tokens);
}

bool
read_list_delimiters(struct token *tokens)
{
	struct token *head = tokens;
	int64_t balanced = 0;

	while (head && head->data) {
		if (*head->data == '(') {
			++balanced;
		} else if (*head->data == ')') {
			--balanced;
		}

		head = head->next;
	}

	if (balanced < 0) {
		fputs("error: read_list_delimiters: missing open parenthesis\n", stderr);
		return false;
	}

	if (balanced > 0) {
		fputs("error: read_list_delimiters: missing closing parenthesis\n", stderr);
		return false;
	}

	return true;
}
