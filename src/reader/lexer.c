// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ctype.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/lexer.h>

struct token const *
lexer(char const *const input)
{
	char const *cursor = input;
	size_t index = 0;
	struct token *tokens = NULL;

	while (*cursor) {
		struct token *token = NULL;

		switch (*cursor) {
		// Whitespace tokens
		case ' ':
			token = lex_token(TOKEN_SPACE, &cursor, &index, " ");
			break;
		case '\n':
			token = lex_token(TOKEN_NEWLINE, &cursor, &index, "\n");
			break;
		case '\r':
			token = lex_token(TOKEN_CARRIAGE_RETURN, &cursor, &index, "\r");
			break;
		case '\t':
			token = lex_token(TOKEN_TAB, &cursor, &index, "\t");
			break;
		case '\v':
			token = lex_token(TOKEN_VERTICAL_TAB, &cursor, &index, "\v");
			break;

		// Single-Character tokens
		case '*':
			token = lex_token(TOKEN_ASTERISK, &cursor, &index, "*");
			break;
		case '`':
			token = lex_token(TOKEN_BACKTICK, &cursor, &index, "`");
			break;
		case '^':
			token = lex_token(TOKEN_CARET, &cursor, &index, "^");
			break;
		case ':':
			token = lex_token(TOKEN_COLON, &cursor, &index, ":");
			break;
		case '=':
			token = lex_token(TOKEN_EQUAL, &cursor, &index, "=");
			break;
		case '#':
			token = lex_token(TOKEN_OCTOTHORPE, &cursor, &index, "#");
			break;
		case '(':
			token = lex_token(TOKEN_PAREN_LEFT, &cursor, &index, "(");
			break;
		case ')':
			token = lex_token(TOKEN_PAREN_RIGHT, &cursor, &index, ")");
			break;
		case '%':
			token = lex_token(TOKEN_PERCENT, &cursor, &index, "%");
			break;
		case '\"':
			token = lex_token(TOKEN_QUOTE_DOUBLE, &cursor, &index, "\"");
			break;
		case '\'':
			token = lex_token(TOKEN_QUOTE_SINGLE, &cursor, &index, "\'");
			break;
		case ';':
			token = lex_token(TOKEN_SEMICOLON, &cursor, &index, ";");
			break;
		case '\\':
			token = lex_token(TOKEN_SLASH_BACKWARD, &cursor, &index, "\\");
			break;
		case '/':
			token = lex_token(TOKEN_SLASH_FORWARD, &cursor, &index, "/");
			break;

		// Multi-Character tokens
		case '-':
			if (isdigit(lexer_peek(cursor))) {
				token = lex_number(&index, &cursor);
			} else if (lexer_peek(cursor) == '>') {
				token = lex_token(TOKEN_ARROW, &cursor, &index, "->");
			} else {
				token = lex_token(TOKEN_MINUS, &cursor, &index, "-");
			}
			break;
		case '+':
			if (isdigit(lexer_peek(cursor))) {
				token = lex_number(&index, &cursor);
			} else {
				token = lex_token(TOKEN_PLUS, &cursor, &index, "+");
			}
			break;
		case '<':
		case '>':
			if (lexer_peek(cursor) == '=') {
				token = lex_token(TOKEN_GREATER_OR_EQUAL, &cursor, &index, ">=");
			} else {
				token = lex_token(TOKEN_GREATER_THAN, &cursor, &index, ">");
			}
			break;

		// Atoms
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
		default:
			token = lex_symbol(&index, &cursor);
			break;
		}

		if (!token || token->type == TOKEN_ERROR) {
			return token;
		}
		tokens = token_append(tokens, token);
	};

	return tokens;
}

char
lexer_peek(char const *input)
{
	char const *cursor = input;
	++cursor;
	return *cursor;
}

struct token *
lex_number(size_t *index, char const **input)
{
	char const *cursor = *input;
	size_t length = 0;

	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (*cursor && isdigit(*cursor) && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}

	char *const number = GC_MALLOC(length + 1);
	memcpy(number, *input, length);
	struct token *const token = new_token(TOKEN_NUMBER, *index, number);
	*input = cursor;
	*index += length;
	return token;
}

struct token *
lex_symbol(size_t *index, char const **input)
{
	char const *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}

	if (length == 0) {
		return new_token(TOKEN_ERROR, *index, "lex_symbol: length is zero");
	}

	char *const symbol = GC_MALLOC(length + 1);
	memcpy(symbol, *input, length);
	struct token *token = new_token(TOKEN_SYMBOL, *index, symbol);
	*input = cursor;
	*index += length;
	return token;
}

struct token *
lex_token(enum token_type type, char const **cursor, size_t *index, char const *const data)
{
	struct token *token = new_token(type, *index, data);
	size_t length = strlen(data);
	*cursor += length;
	*index += length;
	return token;
}
