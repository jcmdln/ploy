// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/parser.h>

void parser_print(Object *object);
void parser_print_list(Object *list);

Object *parse_form(Token **tokens);
Object *parse_keyword(Token **token);
Object *parse_lambda(Token **token);
Object *parse_list(Token **token);
Object *parse_number(Token **token);
Object *parse_quasiquote(Token **token);
Object *parse_quote(Token **token);
Object *parse_string(Token **token);
Object *parse_symbol(Token **token);

Object *
parser(Token *tokens)
{
	if (!tokens) return Error("parser: tokens is NULL");
	if (tokens->type == TOKEN_ERROR) return Error(tokens->data);

	Object *objects = parse_form(&tokens);
	if (!objects) return Error("parser: objects is NULL");

#ifdef PLOY_DEBUG
	puts("objects:");
	parser_print(objects);
#endif // PLOY_DEBUG

	return objects;
}

void
parser_print(Object *object)
{
	if (!object) {
		fputs("error: parser_print: object is NULL\n", stderr);
		return;
	}

	Object *head = object;
	switch (head->type) {
	case OBJECT_NIL:
		printf("%16s: '%s'\n", "nil", "nil");
		break;
	case OBJECT_BOOLEAN:
		printf("%16s: '%s'\n", "boolean", head->boolean ? "true" : "false");
		break;
	case OBJECT_ERROR:
		printf("%16s: '%s'\n", "error", head->atom);
		break;
	case OBJECT_KEYWORD:
		printf("%16s: '%s'\n", "keyword", head->atom);
		break;
	case OBJECT_LAMBDA:
		printf("%16s: '%s'\n", "lambda", "<lambda>");
		break;
	case OBJECT_LIST:
		parser_print_list(head);
		break;
	case OBJECT_NUMBER:
		printf("%16s: '%ld'\n", "number", head->number);
		break;
	case OBJECT_STRING:
		printf("%16s: '%s'\n", "string", head->atom);
		break;
	case OBJECT_SYMBOL:
		printf("%16s: '%s'\n", "symbol", head->atom);
		break;
	}
}

void
parser_print_list(Object *list)
{
	printf("%16s: %s\n", "list", "(");

	if (list->type == OBJECT_LIST) list = Car(list);

	while (list && list->type != OBJECT_NIL) {
		if (list->type != OBJECT_LIST) {
			printf(" . ");
			parser_print(list);
			break;
		}

		Object *car = Car(list);
		Object *cdr = Cdr(list);

		if (car->type == OBJECT_NIL && cdr->type == OBJECT_NIL) {
			list = cdr;
			continue;
		}

		parser_print(car);

		list = cdr;
	}

	printf("%16s: %s\n", "list", ")");
}

Object *
parse_form(Token **tokens)
{
	if (!tokens || !*tokens) return Error("parse_form: tokens is NULL");

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

Object *
parse_keyword(Token **token)
{
	if (!token || !*token) return Error("parse_keyword: token is NULL");
	if ((*token)->type != TOKEN_KEYWORD) return Error("parse_keyword: invalid token->type");

	Token *head = *token;
	*token = head->next;

	char *keyword = GC_MALLOC(sizeof(*keyword));
	memcpy(keyword, head->data, strlen(head->data));

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->atom = keyword;

	return object;
}

Object *
parse_lambda(Token **token)
{
	if (!token || !*token) return Error("parse_lambda: token is NULL");

	Token *head = *token;
	*token = head->next;

	// struct object *object = GC_MALLOC(sizeof(*object));
	// object->type = OBJECT_LAMBDA;
	// object->lambda = GC_MALLOC(sizeof(*object->lambda));
	// object->lambda->env = NULL;
	// object->lambda->args = NULL;
	// object->lambda->body = NULL;
	return Error("parse_lambda: not implemented");
}

Object *
parse_list(Token **token)
{
	if (!token || !*token) return Error("parse_list: token is NULL");
	if ((*token)->type != TOKEN_PAREN_L) return Error("parse_list: missing open parenthesis");

	Token *head = *token;
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

Object *
parse_number(Token **token)
{
	if (!token || !*token) return Error("parse_number: token is NULL");
	if ((*token)->type != OBJECT_NUMBER) return Error("parse_number: missing single_quote");

	Token *head = *token;
	*token = head->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = strtoll(head->data, NULL, 10);

	return object;
}

Object *
parse_quasiquote(Token **token)
{
	if (!token || !*token) return Error("parse_quasiquote: token is NULL");
	if ((*token)->type != TOKEN_BACKTICK) return Error("parse_quasiquote: missing single_quote");

	Token *head = *token;
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

Object *
parse_quote(Token **token)
{
	if (!token || !*token) return Error("parse_quote: token is NULL");
	if ((*token)->type != TOKEN_SINGLE_QUOTE) return Error("parse_quote: missing single_quote");

	Token *head = *token;
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
Object *
parse_string(Token **token)
{
	if (!token || !*token) return Error("parse_string: token is NULL");
	if ((*token)->type != TOKEN_STRING) return Error("parse_string: invalid token->type");

	Token *head = *token;
	*token = head->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->atom = head->data;

	return object;
}

Object *
parse_symbol(Token **token)
{
	if (!token || !*token) return Error("parse_symbol: head is NULL");
	if ((*token)->type != TOKEN_SYMBOL) return Error("parse_symbol: invalid token->type");

	Token *head = *token;
	*token = head->next;

	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->atom = head->data;

	return object;
}
