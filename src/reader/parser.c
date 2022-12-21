// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/parser.h>

struct object *parse_form(struct token **tokens);
struct object *parse_keyword(struct token **token);
struct object *parse_lambda(struct token **token);
struct object *parse_list(struct token **token);
struct object *parse_number(struct token **token);
struct object *parse_quasiquote(struct token **token);
struct object *parse_quote(struct token **token);
struct object *parse_string(struct token **token);
struct object *parse_symbol(struct token **token);

struct object *
parser(struct token *tokens) {
	if (!tokens) {
		return Error("parser: tokens is NULL");
	}
	if (tokens->type == TOKEN_ERROR) {
		return Error(tokens->data);
	}

	struct object *objects = parse_form(&tokens);
	if (!objects) {
		return Error("parser: objects is NULL");
	}

	return objects;
}

struct object *
parse_form(struct token **tokens) {
	if (!tokens) {
		return Error("parse_form: tokens is NULL");
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
			object = Nil();
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

		if (!object) {
			return Error("parse_form: object is NULL");
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
parse_keyword(struct token **token) {
	if (!token) {
		return Error("parse_keyword: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_KEYWORD) {
		return Error("parse_keyword: token->type is not TOKEN_KEYWORD");
	}
	*token = head->next;

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return Keyword(string);
}

struct object *
parse_lambda(struct token **token) {
	if (!token) {
		return Error("parse_lambda: token is NULL");
	}

	struct token *head = *token;
	*token = head->next;

	return Error("parse_lambda: not implemented");
}

struct object *
parse_list(struct token **token) {
	if (!token) {
		return Error("parse_list: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_PAREN_L) {
		return Error("parse_list: missing open parenthesis");
	}
	*token = head->next;

	struct object *object = parse_form(token);
	if (!object) {
		return Error("parse_list: parse_form returned NULL");
	}
	if (object->type == OBJECT_ERROR) {
		return object;
	}

	head = *token;

	if (!head || head->type != TOKEN_PAREN_R) {
		return Error("parse_list: missing closing parenthesis");
	}

	*token = head->next;

	return object;
}

struct object *
parse_number(struct token **token) {
	if (!token) {
		return Error("parse_number: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_NUMBER) {
		return Error("parse_number: token->type is not TOKEN_NUMBER");
	}
	*token = head->next;

	return Number(strtoll(head->data, NULL, 10));
}

struct object *
parse_quasiquote(struct token **token) {
	if (!token) {
		return Error("parse_quasiquote: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_BACKTICK) {
		return Error("parse_quasiquote: missing backtick prefix");
	}
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

struct object *
parse_quote(struct token **token) {
	if (!token) {
		return Error("parse_quote: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_SINGLE_QUOTE) {
		return Error("parse_quote: missing single_quote");
	}
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
struct object *
parse_string(struct token **token) {
	if (!token) {
		return Error("parse_string: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_STRING) {
		return Error("parse_string: token->type is not TOKEN_STRING");
	}
	*token = head->next;

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return String(string);
}

struct object *
parse_symbol(struct token **token) {
	if (!token) {
		return Error("parse_symbol: token is NULL");
	}

	struct token *head = *token;
	if (head->type != TOKEN_SYMBOL) {
		return Error("parse_symbol: token->type is not TOKEN_SYMBOL");
	}

	*token = head->next;

	char *string = GC_MALLOC(sizeof(*string));
	memcpy(string, head->data, strlen(head->data));

	return Symbol(string);
}
