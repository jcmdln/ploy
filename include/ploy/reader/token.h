// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_TOKEN_H
#pragma once

#include <sys/types.h>

static char const TOKENS[24] = " \t\v\n\r*`^:=/><-#()%+;\'\"\0";

enum token_type {
	TOKEN_NIL = 0,
	TOKEN_ERROR,

	// Whitespace tokens
	TOKEN_CARRIAGE_RETURN, // `\r`
	TOKEN_NEWLINE,         // `\n`
	TOKEN_SPACE,           // ` `
	TOKEN_TAB,             // `\t`
	TOKEN_VERTICAL_TAB,    // `\v`

	// Character tokens
	TOKEN_ARROW,            // `->`
	TOKEN_ASTERISK,         // `*`
	TOKEN_BACKTICK,         // '`'
	TOKEN_CARET,            // `^`
	TOKEN_COLON,            // `:`
	TOKEN_EQUAL,            // `=`
	TOKEN_FORWARD_SLASH,    // `/`
	TOKEN_GREATER_OR_EQUAL, // `>=`
	TOKEN_GREATER_THAN,     // `>`
	TOKEN_LESS_OR_EQUAL,    // `<=`
	TOKEN_LESS_THAN,        // `<`
	TOKEN_MINUS,            // `-`
	TOKEN_PAREN_L,          // `(`
	TOKEN_PAREN_R,          // `)`
	TOKEN_PERCENT,          // `%`
	TOKEN_PLUS,             // `+`
	TOKEN_SINGLE_QUOTE,     // `'`

	// Atoms
	TOKEN_COMMENT,
	TOKEN_KEYWORD,
	TOKEN_NUMBER,
	TOKEN_STRING,
	TOKEN_SYMBOL,
};

typedef struct token {
	enum token_type type;
	size_t index;
	const char *data;
	struct token *next;
} const Token;

struct token *new_token(enum token_type type, size_t index, const char *data);

struct token *token_append(struct token *tokens, struct token *token);
void token_print(struct token *tokens);
const char *token_type_as_char(enum token_type type);

#endif // PLOY_READER_TOKEN_H
