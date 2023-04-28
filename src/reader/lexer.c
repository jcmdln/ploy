// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ctype.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/reader/lexer.h>

Token *
lexer(const char *input)
{
	const char *cursor = input;
	size_t index = 0;
	struct token *tokens = NULL;

	while (*cursor) {
		struct token *token = NULL;

		switch (*cursor) {
		// Whitespace tokens
		case ' ':
			token = new_token(TOKEN_SPACE, index, " ");
			++cursor;
			++index;
			break;
		case '\n':
			token = new_token(TOKEN_NEWLINE, index, "\\n");
			++cursor;
			++index;
			break;
		case '\r':
			token = new_token(TOKEN_CARRIAGE_RETURN, index, "\\r");
			++cursor;
			++index;
			break;
		case '\t':
			token = new_token(TOKEN_TAB, index, "\\t");
			++cursor;
			++index;
			break;
		case '\v':
			token = new_token(TOKEN_VERTICAL_TAB, index, "\\v");
			++cursor;
			++index;
			break;

		// Single-Character tokens
		case '*':
			token = new_token(TOKEN_ASTERISK, index, "*");
			++cursor;
			++index;
			break;
		case '`':
			token = new_token(TOKEN_BACKTICK, index, "`");
			++cursor;
			++index;
			break;
		case '^':
			token = new_token(TOKEN_CARET, index, "^");
			++cursor;
			++index;
			break;
		case ':':
			token = new_token(TOKEN_COLON, index, ":");
			++cursor;
			++index;
			break;
		case '=':
			token = new_token(TOKEN_EQUAL, index, "=");
			++cursor;
			++index;
			break;
		case '#':
			token = new_token(TOKEN_OCTOTHORPE, index, "#");
			++cursor;
			++index;
			break;
		case '(':
			token = new_token(TOKEN_PAREN_LEFT, index, "(");
			++cursor;
			++index;
			break;
		case ')':
			token = new_token(TOKEN_PAREN_RIGHT, index, ")");
			++cursor;
			++index;
			break;
		case '%':
			token = new_token(TOKEN_PERCENT, index, "%");
			++cursor;
			++index;
			break;
		case '\"':
			token = new_token(TOKEN_QUOTE_DOUBLE, index, "\"");
			++cursor;
			++index;
			break;
		case '\'':
			token = new_token(TOKEN_QUOTE_SINGLE, index, "\'");
			++cursor;
			++index;
			break;
		case ';':
			token = new_token(TOKEN_SEMICOLON, index, ";");
			++cursor;
			++index;
			break;
		case '\\':
			token = new_token(TOKEN_SLASH_BACKWARD, index, "\\");
			++cursor;
			++index;
			break;
		case '/':
			token = new_token(TOKEN_SLASH_FORWARD, index, "/");
			++cursor;
			++index;
			break;

		// Multi-Character tokens
		case '-':
			if (isdigit(lexer_peek(cursor))) {
				token = lex_number(&index, &cursor);
			} else if (lexer_peek(cursor) == '>') {
				token = new_token(TOKEN_ARROW, index, "->");
				cursor += 2;
				index += 2;
			} else {
				token = new_token(TOKEN_MINUS, index, "-");
				++cursor;
				++index;
			}
			break;
		case '+':
			if (isdigit(lexer_peek(cursor))) {
				token = lex_number(&index, &cursor);
			} else {
				token = new_token(TOKEN_PLUS, index, "+");
				++cursor;
				++index;
			}
			break;
		case '<':
		case '>':
			if (lexer_peek(cursor) == '=') {
				token = new_token(TOKEN_GREATER_OR_EQUAL, index, ">=");
				cursor += 2;
				index += 2;
			} else {
				new_token(TOKEN_GREATER_THAN, index, ">");
				++cursor;
				++index;
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
lexer_peek(const char *input)
{
	const char *cursor = input;
	++cursor;
	return *cursor;
}

struct token *
lex_number(size_t *index, const char **input)
{
	const char *cursor = *input;
	size_t length = 0;

	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (*cursor && isdigit(*cursor) && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}

	char *number = GC_MALLOC(sizeof(*number));
	memcpy(number, *input, length);
	struct token *token = new_token(TOKEN_NUMBER, *index, number);
	*input = cursor;
	*index += length;
	return token;
}

struct token *
lex_symbol(size_t *index, const char **input)
{
	const char *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}

	if (length == 0) {
		return new_token(TOKEN_ERROR, *index, "lex_symbol: length is zero");
	}

	char *symbol = GC_MALLOC(sizeof(*symbol));
	memcpy(symbol, *input, length);
	struct token *token = new_token(TOKEN_SYMBOL, *index, symbol);
	*input = cursor;
	*index += length;
	return token;
}
