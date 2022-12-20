// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/reader/token.h>

struct token *
token_append(struct token *tokens, struct token *token) {
	if (!token) {
		return new_token(TOKEN_ERROR, 0, "token_append: token is NULL");
	}
	if (!tokens) {
		return token;
	}

	struct token *head = tokens;
	while (head && head->next) {
		head = head->next;
	}
	head->next = token;

	return tokens;
}

struct token *
new_token(enum token_type type, size_t index, const char *data) {
	if (!data) {
		return new_token(TOKEN_ERROR, 0, "new_token: data is NULL");
	}

	struct token *token = GC_MALLOC(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = data;

	return token;
}

void
token_print(struct token *tokens) {
	if (!tokens) {
		if (!fputs("error: token_print: tokens is NULL\n", stderr)) {
			exit(EXIT_FAILURE);
		}
		return;
	}

	struct token *head = tokens;
	while (head) {
		printf("token: %16s: '%s'\n", token_type_as_char(head->type), head->data);
		head = head->next;
	}
}

const char *
token_type_as_char(enum token_type type) {
	switch (type) {
	case TOKEN_NIL:
		return "nil";
	case TOKEN_ERROR:
		return "error";

	// Whitespace tokens
	case TOKEN_CARRIAGE_RETURN:
		return "carriage_return";
	case TOKEN_NEWLINE:
		return "newline";
	case TOKEN_SPACE:
		return "space";
	case TOKEN_TAB:
		return "tab";
	case TOKEN_VERTICAL_TAB:
		return "vertical_tab";

	// Character tokens
	case TOKEN_ARROW:
		return "arrow";
	case TOKEN_ASTERISK:
		return "asterisk";
	case TOKEN_BACKTICK:
		return "backtick";
	case TOKEN_EQUAL:
		return "equal";
	case TOKEN_CARET:
		return "caret";
	case TOKEN_COLON:
		return "colon";
	case TOKEN_FORWARD_SLASH:
		return "forward_slash";
	case TOKEN_GREATER_OR_EQUAL:
		return "greater_or_equal";
	case TOKEN_GREATER_THAN:
		return "greater_than";
	case TOKEN_LESS_OR_EQUAL:
		return "less_or_equal";
	case TOKEN_LESS_THAN:
		return "less_than";
	case TOKEN_MINUS:
		return "minus";
	case TOKEN_PAREN_L:
		return "paren_l";
	case TOKEN_PAREN_R:
		return "paren_r";
	case TOKEN_PERCENT:
		return "percent";
	case TOKEN_PLUS:
		return "plus";
	case TOKEN_SINGLE_QUOTE:
		return "single_quote";

	// Atoms
	case TOKEN_COMMENT:
		return "comment";
	case TOKEN_KEYWORD:
		return "keyword";
	case TOKEN_NUMBER:
		return "number";
	case TOKEN_STRING:
		return "string";
	case TOKEN_SYMBOL:
		return "symbol";
	}

	return NULL;
}
