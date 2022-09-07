// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy/builtins.h>
#include <ploy/reader/parser.h>

struct object *
parser(struct token *tokens)
{
	if (!tokens) {
		return NULL;
	}

	struct object *objects = parse_form(&tokens);
	if (!objects) {
		return NULL;
	}

	return objects;
}

struct object *
parse_form(struct token **tokens)
{
	if (!tokens) {
		fputs("error: parse_form: tokens stream is NULL\n", stderr);
		return NULL;
	}

	struct object *objects = NULL;
	struct token *token = *tokens;

	while (token) {
		struct object *object = NULL;

		switch (token->type) {
		// Whitespace
		case TOKEN_CARRIAGE_RETURN:
		case TOKEN_NEWLINE:
		case TOKEN_SPACE:
		case TOKEN_TAB:
		case TOKEN_VERTICAL_TAB:
			*tokens = token = token->next;
			continue;

		// Character tokens
		case TOKEN_PAREN_R:
			*tokens = token;
			return objects;
		case TOKEN_PAREN_L:
			object = parse_list(&token);
			break;

		// Atoms
		case TOKEN_COMMENT:
			// Comments are ignored for now
			*tokens = token = token->next;
			continue;
		case TOKEN_KEYWORD:
			object = parse_keyword(&token);
			break;
		case TOKEN_NUMBER:
			object = parse_number(&token);
			break;
		case TOKEN_STRING:
			object = parse_string(&token);
			break;
		case TOKEN_SYMBOL:
			object = parse_symbol(&token);
			break;

		default:
			printf("error: parse_form: unknown form: '%s' (%s)\n", token->data,
				token_type_as_char(token->type));
			return NULL;
		}

		if (!object) {
			return NULL;
		}

		objects = Append(objects, object);

		if (!token || !token->next) {
			break;
		}
	}

	*tokens = token;

	return objects;
}

struct object *
parse_keyword(struct token **token)
{
	if (!token) {
		fputs("error: parse_keyword: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_KEYWORD) {
		fputs("error: parse_keyword: token->type is not TOKEN_KEYWORD\n", stderr);
		return NULL;
	}

	*token = head->next;

	return object_keyword(strdup(head->data));
}

struct object *
parse_lambda(struct token **token)
{
	if (!token) {
		fputs("error: parse_lambda: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	*token = head->next;

	return NULL;
}

struct object *
parse_list(struct token **token)
{
	if (!token) {
		fputs("error: parse_list: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_PAREN_L || *head->data != '(') {
		fputs("error: parse_list: missing open parenthesis '('\n", stderr);
		return NULL;
	}

	*token = head->next;
	struct object *object = parse_form(token);
	head = *token;

	if (!head || head->type != TOKEN_PAREN_R || *head->data != ')') {
		fputs("error: parse_list: missing closing parenthesis\n", stderr);
		return NULL;
	}

	*token = head->next;

	return object;
}

struct object *
parse_number(struct token **token)
{
	if (!token) {
		fputs("error: parse_number: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_NUMBER) {
		fputs("error: parse_string: token->type is not TOKEN_NUMBER\n", stderr);
		return NULL;
	}

	*token = head->next;

	return object_number(strtoll(head->data, NULL, 10));
}

struct object *
parse_quasiquote(struct token **token)
{
	if (!token) {
		fputs("error: parse_quasiquote: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_BACKTICK || *head->data != '`') {
		fputs("error: parse_quasiquote: missing backtick '`' prefix\n", stderr);
		return NULL;
	}

	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		fputs("error: parse_quasiquote: invalid form\n", stderr);
		return NULL;
	}

	*token = head->next;

	return NULL;
}

struct object *
parse_quote(struct token **token)
{
	if (!token) {
		fputs("error: parse_quote: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_SINGLE_QUOTE) {
		fputs("error: parse_quasiquote: missing single_quote '\''\n", stderr);
		return NULL;
	}

	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		fputs("error: parse_quasiquote: invalid form\n", stderr);
		return NULL;
	}

	*token = head->next;

	return NULL;
}

// FIXME: parse_string: Handle nested strings
struct object *
parse_string(struct token **token)
{
	if (!token) {
		fputs("error: parse_string: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_STRING) {
		fputs("error: parse_string: token->type is not TOKEN_STRING\n", stderr);
		return NULL;
	}

	*token = head->next;

	return object_string(strdup(head->data));
}

struct object *
parse_symbol(struct token **token)
{
	if (!token) {
		fputs("error: parse_symbol: token is NULL\n", stderr);
		return NULL;
	}

	struct token *head = *token;

	if (head->type != TOKEN_SYMBOL) {
		fputs("error: parse_symbol: token->type is not TOKEN_SYMBOL\n", stderr);
		return NULL;
	}

	*token = head->next;

	return object_symbol(strdup(head->data));
}
