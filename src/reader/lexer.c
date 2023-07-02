// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ctype.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/lexer.h>

Token const *
lexer(char const *const input)
{
	char const *cursor = input;
	size_t index = 0;
	Token *tokens = NULL;

	while (*cursor) {
		Token *token = NULL;

		switch (*cursor) {
		// Whitespace
		case ' ':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			++cursor;
			++index;
			continue;

		// Comment
		case '#':
		case ';':
			while (*cursor != '\0' && *cursor != '\n')
				++cursor;
			continue;

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
		case '(':
			token = lex_token(TOKEN_PAREN_LEFT, &cursor, &index, "(");
			break;
		case ')':
			token = lex_token(TOKEN_PAREN_RIGHT, &cursor, &index, ")");
			break;
		case '%':
			token = lex_token(TOKEN_PERCENT, &cursor, &index, "%");
			break;
		case '\'':
			token = lex_token(TOKEN_QUOTE_SINGLE, &cursor, &index, "\'");
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
		case '\"':
			token = lex_string(&index, &cursor);
			break;
		default:
			token = lex_symbol(&index, &cursor);
			break;
		}

		if (!token || token->type == TOKEN_ERROR) return token;
		tokens = token_append(tokens, token);
	};

	return tokens;
}

char
lexer_peek(char const *input)
{
	return input[1];
}

Token *
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

	Token *const token = token_init(TOKEN_NUMBER, number);
	*input = cursor;
	*index += length;
	return token;
}

Token *
lex_string(size_t *index, char const **input)
{
	char const *cursor = *input;
	size_t length = 0;

	if (*cursor != '\"') return token_init(TOKEN_ERROR, "lex_string: Missing open '\"'");
	cursor = ++*input;

	while (*cursor && *cursor != '\"') {
		++cursor;
		++length;
	}

	if (*cursor != '\"') return token_init(TOKEN_ERROR, "lex_string: Missing close '\"'");

	char *const string = GC_MALLOC(length + 1);
	memcpy(string, *input, length);

	Token *token = token_init(TOKEN_STRING, string);
	*input = ++cursor;
	*index += ++length;
	return token;
}

Token *
lex_symbol(size_t *index, char const **input)
{
	char const *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}

	if (length == 0) return token_init(TOKEN_ERROR, "lex_symbol: length is zero");

	char *const symbol = GC_MALLOC(length + 1);
	memcpy(symbol, *input, length);

	Token *token = token_init(TOKEN_SYMBOL, symbol);
	*input = cursor;
	*index += length;
	return token;
}

Token *
lex_token(TokenType type, char const **cursor, size_t *index, char const *const data)
{
	Token *token = token_init(type, data);
	size_t length = strlen(data);
	*cursor += length;
	*index += length;
	return token;
}
