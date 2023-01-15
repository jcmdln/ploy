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
	if (!token) return new_token(TOKEN_ERROR, 0, "token_append: token is NULL");
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
	if (!data) return new_token(TOKEN_ERROR, 0, "new_token: data is NULL");
	struct token *token = GC_MALLOC(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = data;
	return token;
}

void
token_print(Token *tokens)
{
	if (!tokens) {
		fputs("error: token_print: tokens is NULL\n", stderr);
		return;
	}

	puts("{\n  \"tokens\": [");

	Token *head = tokens;
	while (head) {
		printf("    { \"type\": \"%s\", \"index\": %ld, \"data\": \"%s\" },\n",
			token_type_as_char(head->type), head->index, head->data);
		head = head->next;
	}

	puts("  ]\n}");
}

const char *
token_type_as_char(enum token_type type)
{
	switch (type) {
	case TOKEN_NIL:
		return "TOKEN_NIL";
	case TOKEN_ERROR:
		return "TOKEN_ERROR";

	// Whitespace tokens
	case TOKEN_CARRIAGE_RETURN:
		return "TOKEN_CARRIAGE_RETURN";
	case TOKEN_NEWLINE:
		return "TOKEN_NEWLINE";
	case TOKEN_SPACE:
		return "TOKEN_SPACE";
	case TOKEN_TAB:
		return "TOKEN_TAB";
	case TOKEN_VERTICAL_TAB:
		return "TOKEN_VERTICAL_TAB";

	// Character tokens
	case TOKEN_ARROW:
		return "TOKEN_ARROW";
	case TOKEN_ASTERISK:
		return "TOKEN_ASTERISK";
	case TOKEN_BACKTICK:
		return "TOKEN_BACKTICK";
	case TOKEN_EQUAL:
		return "TOKEN_EQUAL";
	case TOKEN_CARET:
		return "TOKEN_CARET";
	case TOKEN_COLON:
		return "TOKEN_COLON";
	case TOKEN_FORWARD_SLASH:
		return "TOKEN_FORWARD_SLASH";
	case TOKEN_GREATER_OR_EQUAL:
		return "TOKEN_GREATER_OR_EQUAL";
	case TOKEN_GREATER_THAN:
		return "TOKEN_GREATER_THAN";
	case TOKEN_LESS_OR_EQUAL:
		return "TOKEN_LESS_OR_EQUAL";
	case TOKEN_LESS_THAN:
		return "TOKEN_LESS_THAN";
	case TOKEN_MINUS:
		return "TOKEN_MINUS";
	case TOKEN_PAREN_L:
		return "TOKEN_PAREN_L";
	case TOKEN_PAREN_R:
		return "TOKEN_PAREN_R";
	case TOKEN_PERCENT:
		return "TOKEN_PERCENT";
	case TOKEN_PLUS:
		return "TOKEN_PLUS";
	case TOKEN_SINGLE_QUOTE:
		return "TOKEN_SINGLE_QUOTE";

	// Atoms
	case TOKEN_COMMENT:
		return "TOKEN_COMMENT";
	case TOKEN_KEYWORD:
		return "TOKEN_KEYWORD";
	case TOKEN_NUMBER:
		return "TOKEN_NUMBER";
	case TOKEN_STRING:
		return "TOKEN_STRING";
	case TOKEN_SYMBOL:
		return "TOKEN_SYMBOL";
	}

	return NULL;
}
