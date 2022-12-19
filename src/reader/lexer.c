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
lexer(const char *input) {
	if (!input) {
		return new_token(TOKEN_ERROR, 0, "lexer: input is NULL");
	}

	char *cursor = (char *)input;
	size_t index = 0;
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
			} else if (*cursor == '-' && lexer_peek(cursor) == '>') {
				token = lex_token(&index, &cursor, 2);
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
			return new_token(TOKEN_ERROR, 0, "lexer: token is NULL");
		}

		tokens = token_append(tokens, token);
	};

	if (!tokens) {
		return new_token(TOKEN_ERROR, 0, "lexer: tokens is NULL");
	}

	return tokens;
}

char
lexer_peek(const char *input) {
	char *cursor = (char *)input;
	++cursor;
	return *cursor;
}

struct token *
lex_comment(size_t *index, char **input) {
	if (!index) {
		return new_token(TOKEN_ERROR, 0, "lex_comment: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, 0, "lex_comment: input is NULL");
	}
	if (**input != '#' && **input != ';') {
		return new_token(TOKEN_ERROR, 0, "lex_comment: input is NULL");
	}

	char *cursor = *input;
	size_t length = 0;
	while (*cursor && *cursor != '\n') {
		++cursor;
		++length;
	};

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, *input, length);
	struct token *token = new_token(TOKEN_COMMENT, *index, string);
	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_keyword(size_t *index, char **input) {
	if (!index) {
		return new_token(TOKEN_ERROR, *index, "lex_keyword: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, *index, "lex_keyword: input is NULL");
	}
	if (**input != ':') {
		return new_token(TOKEN_ERROR, *index, "lex_keyword: lex_keyword: missing colon prefix ':'");
	}

	char *cursor = ++*input;
	size_t length = 0;
	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	if (length == 0) {
		return new_token(TOKEN_ERROR, *index, "lex_keyword: identifier length is zero");
	}

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = new_token(TOKEN_KEYWORD, *index, string);
	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_number(size_t *index, char **input) {
	if (!index) {
		return new_token(TOKEN_ERROR, *index, "lex_number: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, *index, "lex_number: input is NULL");
	}

	char *cursor = *input;
	size_t length = 0;
	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = new_token(TOKEN_NUMBER, *index, string);
	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_string(size_t *index, char **input) {
	if (!index) {
		return new_token(TOKEN_ERROR, *index, "lex_string: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, *index, "lex_string: input is NULL");
	}
	if (**input != '\"') {
		return new_token(TOKEN_ERROR, *index, "lex_string: missing open double-quote '\"'");
	}

	char *cursor = ++*input;
	size_t length = 0;
	while (*cursor && *cursor != '\"') {
		++cursor;
		++length;
	};

	if (*cursor != '\"') {
		return new_token(TOKEN_ERROR, *index, "lex_string: missing closing double-quote '\"'");
	}

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = new_token(TOKEN_STRING, *index, string);
	*input = ++cursor;
	*index += ++length;

	return token;
}

struct token *
lex_symbol(size_t *index, char **input) {
	if (!index) {
		return new_token(TOKEN_ERROR, *index, "lex_symbol: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, *index, "lex_symbol: input is NULL");
	}

	char *cursor = *input;
	size_t length = 0;
	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	};

	if (length == 0) {
		const char str[49] = "lex_symbol: symbol cannot have a length of zero\0";
		return new_token(TOKEN_ERROR, *index, str);
	}

	char *string = (char *)gc_alloc(sizeof(*string));
	memcpy(string, *input, length);

	struct token *token = new_token(TOKEN_SYMBOL, *index, string);
	*input = cursor;
	*index += length;

	return token;
}

struct token *
lex_token(size_t *index, char **input, size_t length) {
	if (!index) {
		return new_token(TOKEN_ERROR, *index, "lex_token: index is NULL");
	}
	if (!input) {
		return new_token(TOKEN_ERROR, *index, "lex_token: input is NULL");
	}
	if (length == 0) {
		return new_token(TOKEN_ERROR, *index, "lex_token: length is zero");
	}

	struct token *token = NULL;
	switch (**input) {
	// Whitespace tokens
	case ' ':
		token = new_token(TOKEN_SPACE, *index, " ");
		break;
	case '\n':
		token = new_token(TOKEN_NEWLINE, *index, "\\n");
		break;
	case '\r':
		token = new_token(TOKEN_CARRIAGE_RETURN, *index, "\\r");
		break;
	case '\t':
		token = new_token(TOKEN_TAB, *index, "\\t");
		break;
	case '\v':
		token = new_token(TOKEN_VERTICAL_TAB, *index, "\\v");
		break;

	// Character tokens
	case '*':
		token = new_token(TOKEN_ASTERISK, *index, "*");
		break;
	case '`':
		token = new_token(TOKEN_BACKTICK, *index, "`");
		break;
	case '^':
		token = new_token(TOKEN_CARET, *index, "^");
		break;
	case '=':
		token = new_token(TOKEN_EQUAL, *index, "=");
		break;
	case '/':
		token = new_token(TOKEN_FORWARD_SLASH, *index, "/");
		break;
	case '-':
		if (lexer_peek(*input) == '>') {
			token = new_token(TOKEN_ARROW, *index, "->");
		} else {
			token = new_token(TOKEN_MINUS, *index, "-");
		}
		break;
	case '(':
		token = new_token(TOKEN_PAREN_L, *index, "(");
		break;
	case ')':
		token = new_token(TOKEN_PAREN_R, *index, ")");
		break;
	case '%':
		token = new_token(TOKEN_PERCENT, *index, "%");
		break;
	case '+':
		token = new_token(TOKEN_PLUS, *index, "+");
		break;
	case '\'':
		token = new_token(TOKEN_SINGLE_QUOTE, *index, "\'");
		break;
	case '>':
		if (length == 1) {
			token = new_token(TOKEN_GREATER_THAN, *index, ">");
		} else if (length == 2 && lexer_peek(*input) == '=') {
			token = new_token(TOKEN_GREATER_OR_EQUAL, *index, ">=");
		}
		break;
	case '<':
		if (length == 1) {
			token = new_token(TOKEN_LESS_THAN, *index, "<");
		} else if (length == 2 && lexer_peek(*input) == '=') {
			token = new_token(TOKEN_LESS_OR_EQUAL, *index, "<=");
		}
		break;
	}

	if (!token) {
		char *string = (char *)gc_alloc(sizeof(*string));
		memcpy(string, *input, length);
		token = new_token(TOKEN_ERROR, *index, string);
	}

	*input += length;
	*index += length;

	return token;
}

struct token *
token_append(struct token *tokens, struct token *token) {
	if (!token) {
		return new_token(TOKEN_ERROR, 0, "token_append: token is NULL");
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
new_token(enum token_type type, size_t index, const char *data) {
	if (!data) {
		return new_token(TOKEN_ERROR, 0, "new_token: data is NULL");
	}

	struct token *token = (struct token *)gc_alloc(sizeof(*token));
	token->type = type;
	token->index = index;
	token->data = data;

	return token;
}

void
token_print(struct token *tokens) {
	if (!tokens) {
		if (!fputs("error: token_print: tokens is NULL\n", stderr)) {
			exit(EXIT_FAILURE);
		}
		return;
	}

	struct token *head = tokens;
	while (head) {
		printf("token: %16s: '%s'\n", token_type_as_char(head->type), head->data);
		head = head->next;
	}
}

const char *
token_type_as_char(enum token_type type) {
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
	case TOKEN_ARROW:
		return "arrow";
	case TOKEN_ASTERISK:
		return "asterisk";
	case TOKEN_BACKTICK:
		return "backtick";
	case TOKEN_EQUAL:
		return "equal";
	case TOKEN_CARET:
		return "caret";
	case TOKEN_COLON:
		return "colon";
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
	case TOKEN_PAREN_L:
		return "paren_l";
	case TOKEN_PAREN_R:
		return "paren_r";
	case TOKEN_PERCENT:
		return "percent";
	case TOKEN_PLUS:
		return "plus";
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
