// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy/gc.h>
#include <ploy/reader/lexer.h>

struct token *
lexer(char *input)
{
	if (!input) {
		fputs("error: lexer: input is NULL\n", stderr);
	}

	char *cursor = input;
	int64_t index = 0;
	struct token *tokens = NULL;

	while (*cursor) {
		struct token *token = NULL;

		switch (*cursor) {
		// Whitespace tokens
		case ' ':
		case '\n':
		case '\r':
		case '\t':
		case '\v':

		// Character tokens
		case '*':
		case '`':
		case '=':
		case '^':
		case '/':
		case '(':
		case ')':
		case '%':
		case '\'':
			token = lex_token(&index, &cursor, 1);
			break;
		case '-':
		case '+':
			if (isdigit(lexer_peek(cursor))) {
				token = lex_number(&index, &cursor);
			} else {
				token = lex_token(&index, &cursor, 1);
			}
			break;
		case '<':
		case '>':
			if (lexer_peek(cursor) == '=') {
				token = lex_token(&index, &cursor, 2);
			} else {
				token = lex_token(&index, &cursor, 1);
			}
			break;

		// Atoms
		case '#':
		case ';':
			token = lex_comment(&index, &cursor);
			break;
		case ':':
			token = lex_keyword(&index, &cursor);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			token = lex_number(&index, &cursor);
			break;
		case '\"':
			token = lex_string(&index, &cursor);
			break;
		default:
			token = lex_symbol(&index, &cursor);
			break;
		}

		if (!token) {
			return NULL;
		}

		tokens = token_append(tokens, token);
	};

	if (!tokens) {
		fputs("error: lexer: tokens is NULL\n", stderr);
		return NULL;
	}

	return tokens;
}

char
lexer_peek(char *input)
{
	char *cursor = input;
	++cursor;
	return *cursor;
}

struct token *
lex_comment(int64_t *index, char **input)
{
	if (!index) {
		fputs("error: lex_comment: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_comment: input is NULL\n", stderr);
		return NULL;
	}

	if (**input != '#' && **input != ';') {
		fputs("error: lex_comment: input is NULL\n", stderr);
		return NULL;
	}

	char *cursor = *input;
	int64_t length = 0;

	while (*cursor && *cursor != '\n') {
		++cursor;
		++length;
	};

	char *string = gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = token_new(TOKEN_COMMENT, *index, string);

	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_keyword(int64_t *index, char **input)
{
	if (!index) {
		fputs("error: lex_keyword: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_keyword: input is NULL\n", stderr);
		return NULL;
	}

	if (**input != ':') {
		fputs("error: lex_keyword: missing colon prefix ':'\n", stderr);
		return NULL;
	}

	char *cursor = ++*input;
	int64_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	if (length == 0) {
		fputs("error: lex_keyword: identifier length is zero\n", stderr);
		return NULL;
	}

	char *string = gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = token_new(TOKEN_KEYWORD, *index, string);

	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_number(int64_t *index, char **input)
{
	if (!index) {
		fputs("error: lex_number: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_number: input is NULL\n", stderr);
		return NULL;
	}

	char *cursor = *input;
	int64_t length = 0;

	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	char *string = gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = token_new(TOKEN_NUMBER, *index, string);

	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_string(int64_t *index, char **input)
{
	if (!index) {
		fputs("error: lex_string: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_string: input is NULL\n", stderr);
		return NULL;
	}

	if (**input != '\"') {
		fputs("error: lex_string: missing open double-quote '\"'\n", stderr);
		return NULL;
	}

	char *cursor = ++*input;
	int64_t length = 0;

	while (*cursor && *cursor != '\"') {
		++cursor;
		++length;
	};

	if (*cursor != '\"') {
		fputs("error: lex_string: missing closing double-quote '\"'\n", stderr);
		return NULL;
	}

	char *string = gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = token_new(TOKEN_STRING, *index, string);

	*input = ++cursor;
	*index += ++length;

	return token;
}

struct token *
lex_symbol(int64_t *index, char **input)
{
	if (!index) {
		fputs("error: lex_symbol: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_symbol: input is NULL\n", stderr);
		return NULL;
	}

	char *cursor = *input;
	int64_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	if (length == 0) {
		fputs("error: lex_symbol: symbol cannot have a length of zero\n", stderr);
		return NULL;
	}

	char *string = gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = token_new(TOKEN_SYMBOL, *index, string);

	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_token(int64_t *index, char **input, int64_t length)
{
	if (!index) {
		fputs("error: lex_token: index is NULL\n", stderr);
		return NULL;
	}

	if (!input) {
		fputs("error: lex_token: input is NULL\n", stderr);
		return NULL;
	}

	if (length == 0) {
		fputs("error: lex_token: length is zero\n", stderr);
		return NULL;
	}

	struct token *token = NULL;

	switch (**input) {
	// Whitespace tokens
	case ' ':
		token = token_new(TOKEN_SPACE, *index, " ");
		break;
	case '\n':
		token = token_new(TOKEN_NEWLINE, *index, "\n");
		break;
	case '\r':
		token = token_new(TOKEN_CARRIAGE_RETURN, *index, "\r");
		break;
	case '\t':
		token = token_new(TOKEN_TAB, *index, "\t");
		break;
	case '\v':
		token = token_new(TOKEN_VERTICAL_TAB, *index, "\v");
		break;

	// Character tokens
	case '*':
		token = token_new(TOKEN_ASTERISK, *index, "*");
		break;
	case '`':
		token = token_new(TOKEN_BACKTICK, *index, "`");
		break;
	case '^':
		token = token_new(TOKEN_CARET, *index, "^");
		break;
	case '=':
		token = token_new(TOKEN_EQUAL, *index, "=");
		break;
	case '/':
		token = token_new(TOKEN_FORWARD_SLASH, *index, "/");
		break;
	case '-':
		token = token_new(TOKEN_MINUS, *index, "-");
		break;
	case '(':
		token = token_new(TOKEN_PAREN_L, *index, "(");
		break;
	case ')':
		token = token_new(TOKEN_PAREN_R, *index, ")");
		break;
	case '%':
		token = token_new(TOKEN_PERCENT, *index, "%");
		break;
	case '+':
		token = token_new(TOKEN_PLUS, *index, "+");
		break;
	case '\'':
		token = token_new(TOKEN_SINGLE_QUOTE, *index, "\'");
		break;
	case '>':
		if (length == 1) {
			token = token_new(TOKEN_GREATER_THAN, *index, ">");
		} else if (length == 2 && lexer_peek(*input) == '=') {
			token = token_new(TOKEN_GREATER_OR_EQUAL, *index, ">=");
		}
		break;
	case '<':
		if (length == 1) {
			token = token_new(TOKEN_LESS_THAN, *index, "<");
		} else if (length == 2 && lexer_peek(*input) == '=') {
			token = token_new(TOKEN_LESS_OR_EQUAL, *index, "<=");
		}
		break;
	}

	if (!token) {
		char *string = gc_alloc(sizeof(*string));
		memcpy(string, *input, length);
		token = token_new(TOKEN_ERROR, *index, string);
	}

	*input += length;
	*index += length;

	return token;
}

struct token *
token_append(struct token *tokens, struct token *token)
{
	if (!token) {
		fputs("error: token_append: token is NULL\n", stderr);
		return NULL;
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
token_new(enum token_type type, int64_t index, char *data)
{
	if (!data) {
		printf("error: token_new: %s: data is NULL\n", token_type_as_char(type));
		return NULL;
	}

	struct token *token = gc_alloc(sizeof(*token));

	token->type = type;
	token->index = index;
	token->data = data;

	return token;
}

struct token *
token_peek(struct token *token)
{
	if (!token) {
		printf("error: token_peek: token is NULL\n");
		return NULL;
	}

	if (!token->next) {
		printf("error: token_peek: token->next is NULL\n");
		return NULL;
	}

	return token->next;
}

void
token_print(struct token *tokens)
{
	if (!tokens) {
		fputs("error: token_print: tokens cannot be NULL\n", stderr);
		return;
	}

	struct token *head = tokens;

	while (head) {
		printf("token: %16s: '%s'\n", token_type_as_char(head->type), head->data);
		head = head->next;
	}
}

char *
token_type_as_char(enum token_type type)
{
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
	case TOKEN_ASTERISK:
		return "asterisk";
	case TOKEN_BACKTICK:
		return "backtick";
	case TOKEN_EQUAL:
		return "equal";
	case TOKEN_CARET:
		return "exponent";
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
	case TOKEN_OCTOTHORPE:
		return "octothorpe";
	case TOKEN_PAREN_L:
		return "paren_l";
	case TOKEN_PAREN_R:
		return "paren_r";
	case TOKEN_PERCENT:
		return "percent";
	case TOKEN_PLUS:
		return "plus";
	case TOKEN_SEMICOLON:
		return "semicolon";
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
