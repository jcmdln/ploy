// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ploy/reader.h>
#include <ploy/type/object.h>

struct object *
reader(const char *input)
{
	if (!input) {
		return object_error("reader: input is NULL");
	}

	struct token *tokens = lexer(input);
	if (!tokens) {
		return object_error("reader: tokens is NULL");
	}
	if (tokens->type == TOKEN_ERROR) {
		return object_error(tokens->data);
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

	return object_nil();
}
