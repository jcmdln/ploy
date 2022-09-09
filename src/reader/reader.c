// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <string.h>

#include <ploy/reader.h>
#include <ploy/type/object.h>

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

	struct object *object = read_list_delimiters(tokens);
	if (object && object->type == OBJECT_ERROR) {
		return object;
	}

	return parser(tokens);
}

struct object *
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
		return object_error("read_list_delimiters: missing open parenthesis");
	}

	if (balanced > 0) {
		return object_error("read_list_delimiters: missing closing parenthesis");
	}

	return NULL;
}
