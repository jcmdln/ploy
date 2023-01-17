// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/parser.h>

Object *
parser(Token *tokens)
{
	return parse_form(&tokens);
}

Object *
parse_form(Token **tokens)
{
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

		if (object->type == OBJECT_ERROR) return object;
		objects = Append(objects, object);
		if (!token || !token->next || object->type == OBJECT_NIL) break;
	}

	*tokens = token;
	return objects;
}

Object *
parse_keyword(Token **token)
{
	if ((*token)->type != TOKEN_KEYWORD) return Error("parse_keyword: invalid token->type");

	char *keyword = GC_MALLOC(sizeof(*keyword));
	memcpy(keyword, (*token)->data, strlen((*token)->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->atom = keyword;
	*token = (*token)->next;
	return object;
}

Object *
parse_lambda(Token **token)
{
	// Token *head = *token;
	// *token = head->next;
	// struct object *object = GC_MALLOC(sizeof(*object));
	// object->type = OBJECT_LAMBDA;
	// object->lambda = GC_MALLOC(sizeof(*object->lambda));
	// object->lambda->env = NULL;
	// object->lambda->args = NULL;
	// object->lambda->body = NULL;

	if (token) {
	};
	return Error("parse_lambda: not implemented");
}

Object *
parse_list(Token **token)
{
	if ((*token)->type != TOKEN_PAREN_L) return Error("parse_list: missing open parenthesis");
	*token = (*token)->next;

	Object *object = parse_form(token);
	if (object->type == OBJECT_ERROR) return object;
	if ((*token)->type != TOKEN_PAREN_R) return Error("parse_list: missing closing parenthesis");
	*token = (*token)->next;
	return object;
}

Object *
parse_number(Token **token)
{
	if ((*token)->type != TOKEN_NUMBER) return Error("parse_number: not a number");

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = strtoll((*token)->data, NULL, 10);
	*token = (*token)->next;
	return object;
}

Object *
parse_quasiquote(Token **token)
{
	if ((*token)->type != TOKEN_BACKTICK) return Error("parse_quasiquote: missing single_quote");
	*token = (*token)->next;

	switch ((*token)->type) {
	case TOKEN_PAREN_L:
	case TOKEN_SYMBOL:
		break;
	default:
		return Error("parse_quasiquote: invalid form");
	}

	*token = (*token)->next;
	return Error("parse_quasiquote: not implemented");
}

Object *
parse_quote(Token **token)
{
	if ((*token)->type != TOKEN_SINGLE_QUOTE) return Error("parse_quote: missing single_quote");
	*token = (*token)->next;

	Object *object = &Nil;
	switch ((*token)->type) {
	case TOKEN_PAREN_L:
		object = parse_list(token);
		break;
	case TOKEN_SYMBOL:
		object = parse_symbol(token);
		break;
	default:
		return Error("parse_quote: invalid form");
	}

	*token = (*token)->next;
	return object;
}

// FIXME: parse_string: Handle nested strings
Object *
parse_string(Token **token)
{
	if ((*token)->type != TOKEN_STRING) return Error("parse_string: invalid token->type");

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, (*token)->data, strlen((*token)->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->atom = string;
	*token = (*token)->next;
	return object;
}

Object *
parse_symbol(Token **token)
{
	if ((*token)->type != TOKEN_SYMBOL) return Error("parse_symbol: invalid token->type");

	char *symbol = GC_MALLOC(sizeof(*symbol));
	memcpy(symbol, (*token)->data, strlen((*token)->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->atom = symbol;
	*token = (*token)->next;
	return object;
}
