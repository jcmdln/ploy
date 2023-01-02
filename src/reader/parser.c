// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/parser.h>

Object *parse_form(Token **tokens);
Object *parse_keyword(Token **token);
Object *parse_lambda(Token **token);
Object *parse_list(Token **token);
Object *parse_number(Token **token);
Object *parse_quasiquote(Token **token);
Object *parse_quote(Token **token);
Object *parse_string(Token **token);
Object *parse_symbol(Token **token);

Object *parser(Token *tokens) {
	if (!tokens) return Error("parser: tokens is NULL");
	if (tokens->type == TOKEN_ERROR) return Error(tokens->data);

	Object *objects = parse_form(&tokens);
	if (!objects) return Error("parser: objects is NULL");
	return objects;
}

Object *parse_form(Token **tokens) {
	if (!tokens) return Error("parse_form: tokens is NULL");

	Object *objects = NULL;
	Token *token = *tokens;
	while (token) {
		Object *object = NULL;

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
		// case TOKEN_ARROW:
		// case TOKEN_ASTERISK:
		// case TOKEN_BACKTICK:
		// case TOKEN_CARET:
		// case TOKEN_COLON:
		// case TOKEN_EQUAL:
		// case TOKEN_FORWARD_SLASH:
		// case TOKEN_GREATER_OR_EQUAL:
		// case TOKEN_GREATER_THAN:
		// case TOKEN_LESS_OR_EQUAL:
		// case TOKEN_LESS_THAN:
		// case TOKEN_MINUS:
		case TOKEN_PAREN_R:
			object = &Nil;
			break;
		case TOKEN_PAREN_L:
			object = parse_list(&token);
			break;
		// case TOKEN_PERCENT:
		// case TOKEN_PLUS:
		// case TOKEN_SINGLE_QUOTE:

		// Atoms
		case TOKEN_COMMENT:
			// `parse_form` ignores comments
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
			return Error("parse_form: unknown form");
		}

		if (!object) return Error("parse_form: object is NULL");
		if (object->type == OBJECT_ERROR) return object;
		objects = Append(objects, object);
		if (!token || !token->next || object->type == OBJECT_NIL) break;
	}

	*tokens = token;
	return objects;
}

Object *parse_keyword(Token **token) {
	if (!token) return Error("parse_keyword: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_keyword: head is NULL");
	if (head->type != TOKEN_KEYWORD) return Error("parse_keyword: invalid token->type");
	*token = head->next;

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->keyword = string;
	return object;
}

Object *parse_lambda(Token **token) {
	if (!token) return Error("parse_lambda: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_lambda: head is NULL");
	*token = head->next;

	// struct object *object = GC_MALLOC(sizeof(*object));
	// object->type = OBJECT_LAMBDA;
	// object->lambda = GC_MALLOC(sizeof(*object->lambda));
	// object->lambda->env = NULL;
	// object->lambda->args = NULL;
	// object->lambda->body = NULL;
	return Error("parse_lambda: not implemented");
}

Object *parse_list(Token **token) {
	if (!token) return Error("parse_list: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_list: head is NULL");
	if (head->type != TOKEN_PAREN_L) return Error("parse_list: missing open parenthesis");
	*token = head->next;

	Object *object = parse_form(token);
	if (!object) return Error("parse_list: parse_form returned NULL");
	if (object->type == OBJECT_ERROR) return object;
	head = *token;

	if (!head || head->type != TOKEN_PAREN_R)
		return Error("parse_list: missing closing parenthesis");
	*token = head->next;
	return object;
}

Object *parse_number(Token **token) {
	if (!token) return Error("parse_number: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_number: head is NULL");
	if (head->type != TOKEN_NUMBER) return Error("parse_number: invalid token->type");
	*token = head->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = strtoll(head->data, NULL, 10);
	return object;
}

Object *parse_quasiquote(Token **token) {
	if (!token) return Error("parse_quasiquote: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_quasiquote: head is NULL");
	if (head->type != TOKEN_BACKTICK) return Error("parse_quasiquote: missing backtick prefix");
	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		return Error("parse_quasiquote: invalid form");
	}

	*token = head->next;
	return Error("parse_quasiquote: not implemented");
}

Object *parse_quote(Token **token) {
	if (!token) return Error("parse_quote: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_quote: head is NULL");
	if (head->type != TOKEN_SINGLE_QUOTE) return Error("parse_quote: missing single_quote");
	head = head->next;

	switch (head->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		return Error("parse_quote: invalid form");
	}

	*token = head->next;
	return Error("parse_quote: not implemented");
}

// FIXME: parse_string: Handle nested strings
Object *parse_string(Token **token) {
	if (!token) return Error("parse_string: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_string: head is NULL");
	if (head->type != TOKEN_STRING) return Error("parse_string: invalid token->type");
	*token = head->next;

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->string = string;
	return object;
}

Object *parse_symbol(Token **token) {
	if (!token) return Error("parse_symbol: token is NULL");

	Token *head = *token;
	if (!head) return Error("parse_symbol: head is NULL");
	if (head->type != TOKEN_SYMBOL) return Error("parse_symbol: invalid token->type");
	*token = head->next;

	char *symbol = GC_MALLOC(sizeof(*symbol));
	memcpy(symbol, head->data, strlen(head->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->symbol = symbol;
	return object;
}
