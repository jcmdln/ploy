// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/ploy.h>
#include <ploy/reader/parser.h>

Object const *
parser(Token const *tokens)
{
	return parse_form(&tokens);
}

Object const *
parse_form(Token const **tokens)
{
	Object const *objects = NULL;
	Token const *token = *tokens;

	while (token) {
		Object const *object = NULL;

		switch (token->type) {
		// Character tokens
		// case TOKEN_ARROW:
		// case TOKEN_ASTERISK:
		// case TOKEN_BACKTICK:
		// case TOKEN_CARET:
		case TOKEN_COLON:
			object = parse_keyword(&token);
			break;
		// case TOKEN_EQUAL:
		// case TOKEN_FORWARD_SLASH:
		// case TOKEN_GREATER_OR_EQUAL:
		// case TOKEN_GREATER_THAN:
		// case TOKEN_LESS_OR_EQUAL:
		// case TOKEN_LESS_THAN:
		// case TOKEN_MINUS:
		case TOKEN_PAREN_RIGHT:
			object = &Nil;
			break;
		case TOKEN_PAREN_LEFT:
			object = parse_list(&token);
			break;
		// case TOKEN_PERCENT:
		// case TOKEN_PLUS:
		case TOKEN_QUOTE_DOUBLE:
			object = parse_string(&token);
			break;
			// case TOKEN_SINGLE_QUOTE:

		// Atoms
		case TOKEN_NUMBER:
			object = parse_number(&token);
			break;
		case TOKEN_SYMBOL:
			object = parse_symbol(&token);
			break;

		default:
			return Error(token->data);
		}

		if (object->type == OBJECT_ERROR) return object;
		objects = Append(objects, object);
		if (!token || !token->next || object->type == OBJECT_NIL) break;
	}

	*tokens = token;
	return objects;
}

Object const *
parse_keyword(Token const **token)
{
	Token const *const form = *token;
	if (form->type != TOKEN_COLON || form->next->type != TOKEN_SYMBOL)
		return Error("parse_keyword: invalid form");

	char *const keyword = GC_MALLOC(strlen(form->data) + 1);
	(void)sprintf(keyword, "%s", form->next->data);
	*token = form->next->next;

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->keyword = keyword;
	return object;
}

Object const *
parse_list(Token const **token)
{
	Token const *form = *token;
	if (form->type != TOKEN_PAREN_LEFT) return Error("parse_list: missing open parenthesis");
	form = form->next;

	Object const *const object = parse_form(&form);
	if (object->type == OBJECT_ERROR) return object;
	if (form->type != TOKEN_PAREN_RIGHT) return Error("parse_list: missing closing parenthesis");

	*token = form->next;
	return object;
}

Object const *
parse_number(Token const **token)
{
	Token const *const form = *token;
	if (form->type != TOKEN_NUMBER) return Error("parse_number: not a number");

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = strtoll(form->data, NULL, 10);

	*token = form->next;
	return object;
}

// FIXME: parse_string: Handle nested strings
Object const *
parse_string(Token const **token)
{
	Token const *form = *token;
	if (form->type != TOKEN_QUOTE_DOUBLE) return Error("parse_string: invalid token->type");
	form = form->next;

	char *string = GC_MALLOC(sizeof(*string));
	while (form && form->type != TOKEN_QUOTE_DOUBLE) {
		string = GC_REALLOC(string, strlen(string) + strlen(form->data) + 1);
		(void)sprintf(string, "%s%s", string, form->data);
		form = form->next;
	}

	if (!form || form->type != TOKEN_QUOTE_DOUBLE)
		return Error("parse_string: missing closing '\"'");
	*token = form->next;

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->string = string;
	return object;
}

Object const *
parse_symbol(Token const **token)
{
	Token const *const form = *token;
	if (form->type != TOKEN_SYMBOL) return Error("parse_symbol: invalid token->type");

	char *const symbol = GC_MALLOC(strlen(form->data) + 1);
	(void)sprintf(symbol, "%s", form->data);
	*token = form->next;

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->symbol = symbol;
	return object;
}
