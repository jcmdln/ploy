// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/core.h>
#include <ploy/reader/parser.h>

const struct object *
parser(const struct token *tokens)
{
	return parse_form(&tokens);
}

const struct object *
parse_form(const struct token **tokens)
{
	const struct object *objects = NULL;
	const struct token *token = *tokens;

	while (token) {
		const struct object *object = NULL;

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
		case TOKEN_OCTOTHORPE:
		case TOKEN_SEMICOLON:
			while (token->type != TOKEN_NEWLINE) {
				token = token->next;
			}
			continue;
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
			return Error("parse_form: unknown form");
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

const struct object *
parse_keyword(const struct token **token)
{
	if ((*token)->type != TOKEN_COLON || (*token)->next->type != TOKEN_SYMBOL) {
		return Error("parse_keyword: invalid form");
	}

	char *keyword = GC_MALLOC(sizeof(*keyword));
	sprintf(keyword, "%s", (*token)->next->data);
	*token = (*token)->next->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->atom = keyword;
	return object;
}

const struct object *
parse_list(const struct token **token)
{
	if ((*token)->type != TOKEN_PAREN_LEFT) {
		return Error("parse_list: missing open parenthesis");
	}
	*token = (*token)->next;

	const struct object *object = parse_form(token);
	if (object->type == OBJECT_ERROR) {
		return object;
	}
	if ((*token)->type != TOKEN_PAREN_RIGHT) {
		return Error("parse_list: missing closing parenthesis");
	}

	*token = (*token)->next;
	return object;
}

const struct object *
parse_number(const struct token **token)
{
	if ((*token)->type != TOKEN_NUMBER) {
		return Error("parse_number: not a number");
	}

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = strtoll((*token)->data, NULL, 10);

	*token = (*token)->next;
	return object;
}

// FIXME: parse_string: Handle nested strings
const struct object *
parse_string(const struct token **token)
{
	const struct token *form = *token;

	if (form->type != TOKEN_QUOTE_DOUBLE) {
		return Error("parse_string: invalid token->type");
	}
	form = form->next;

	char *string = GC_MALLOC(sizeof(*string));
	while (form && form->type != TOKEN_QUOTE_DOUBLE) {
		sprintf(string, "%s%s", string, form->data);
		form = form->next;
	}

	if (!form || form->type != TOKEN_QUOTE_DOUBLE) {
		return Error("parse_string: missing closing '\"'");
	}
	*token = form->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->atom = string;
	return object;
}

const struct object *
parse_symbol(const struct token **token)
{
	if ((*token)->type != TOKEN_SYMBOL) {
		return Error("parse_symbol: invalid token->type");
	}

	char *symbol = GC_MALLOC(sizeof(*symbol));
	sprintf(symbol, "%s", (*token)->data);
	*token = (*token)->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->atom = symbol;
	return object;
}
