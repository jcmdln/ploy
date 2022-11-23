// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy/builtins.h>
#include <ploy/gc.h>
#include <ploy/reader/parser.h>

struct object *
parser(struct token *tokens)
{
	if (!tokens) {
		return object_error("parser: tokens is NULL");
	}
	if (tokens->type == TOKEN_ERROR) {
		return object_error(tokens->data);
	}

	struct object *objects = parse_form(&tokens);
	if (!objects) {
		return object_error("parser: objects is NULL");
	}

	return objects;
}

struct object *
parse_form(struct token **tokens)
{
	if (!tokens) {
		return object_error("parse_form: tokens stream is NULL");
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
			object = object_nil();
			break;
		case TOKEN_PAREN_L:
			object = parse_list(&token);
			break;

		// Atoms
		case TOKEN_COMMENT: // Comments are ignored
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
			return object_error("parse_form: unknown form");
		}

		if (!object) {
			return object_error("parse_form: object is NULL");
		}
		if (object->type == OBJECT_ERROR) {
			return object;
		}

		objects = Append(objects, object);

		if (!token || !token->next || object->type == OBJECT_NIL) {
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
		return object_error("parse_keyword: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_KEYWORD) {
		return object_error("parse_keyword: token->type is not TOKEN_KEYWORD");
	}
	*token = head->next;

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return object_keyword(string);
}

struct object *
parse_lambda(struct token **token)
{
	if (!token) {
		return object_error("parse_lambda: token is NULL");
	}

	struct token *head = *token;
	*token = head->next;

	return object_error("parse_lambda: not implemented");
}

struct object *
parse_list(struct token **token)
{
	if (!token) {
		return object_error("parse_list: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_PAREN_L) {
		return object_error("parse_list: missing open parenthesis");
	}
	*token = head->next;

	struct object *object = parse_form(token);
	head = *token;

	if (!head || head->type != TOKEN_PAREN_R) {
		return object_error("parse_list: missing closing parenthesis");
	}

	*token = head->next;

	return object;
}

struct object *
parse_number(struct token **token)
{
	if (!token) {
		return object_error("parse_number: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_NUMBER) {
		return object_error("parse_number: token->type is not TOKEN_NUMBER");
	}
	*token = head->next;

	return object_number(strtoll(head->data, NULL, 10));
}

struct object *
parse_quasiquote(struct token **token)
{
	if (!token) {
		return object_error("parse_quasiquote: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_BACKTICK) {
		return object_error("parse_quasiquote: missing backtick prefix");
	}
	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		return object_error("parse_quasiquote: invalid form");
	}

	*token = head->next;

	return object_error("parse_quasiquote: not implemented");
}

struct object *
parse_quote(struct token **token)
{
	if (!token) {
		return object_error("parse_quote: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_SINGLE_QUOTE) {
		return object_error("parse_quote: missing single_quote");
	}
	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		return object_error("parse_quote: invalid form");
	}

	*token = head->next;

	return object_error("parse_quote: not implemented");
}

// FIXME: parse_string: Handle nested strings
struct object *
parse_string(struct token **token)
{
	if (!token) {
		return object_error("parse_string: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_STRING) {
		return object_error("parse_string: token->type is not TOKEN_STRING");
	}
	*token = head->next;

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return object_string(string);
}

struct object *
parse_symbol(struct token **token)
{
	if (!token) {
		return object_error("parse_symbol: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_SYMBOL) {
		return object_error("parse_symbol: token->type is not TOKEN_SYMBOL");
	}
	*token = head->next;

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return object_symbol(string);
}
