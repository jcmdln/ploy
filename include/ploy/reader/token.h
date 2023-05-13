// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_TOKEN_H
#pragma once

#include <sys/types.h>

static char const TOKENS[24] = " \t\v\n\r*`^:=/><-#()%+;\'\"\0";

enum token_type {
	TOKEN_NIL = 0,
	TOKEN_ERROR,

	// Whitespace tokens
	TOKEN_CARRIAGE_RETURN, /* \r */
	TOKEN_NEWLINE,         /* \n */
	TOKEN_SPACE,           /* \s */
	TOKEN_TAB,             /* \t */
	TOKEN_VERTICAL_TAB,    /* \v */

	// Character tokens
	TOKEN_ARROW,            /* -> */
	TOKEN_ASTERISK,         /* * */
	TOKEN_BACKTICK,         /* ` */
	TOKEN_CARET,            /* ^ */
	TOKEN_COLON,            /* : */
	TOKEN_EQUAL,            /* = */
	TOKEN_GREATER_OR_EQUAL, /* >= */
	TOKEN_GREATER_THAN,     /* > */
	TOKEN_LESS_OR_EQUAL,    /* <= */
	TOKEN_LESS_THAN,        /* < */
	TOKEN_MINUS,            /* - */
	TOKEN_OCTOTHORPE,       /* # */
	TOKEN_PAREN_LEFT,       /* ( */
	TOKEN_PAREN_RIGHT,      /* ) */
	TOKEN_PERCENT,          /* % */
	TOKEN_PLUS,             /* + */
	TOKEN_QUOTE_DOUBLE,     /* " */
	TOKEN_QUOTE_SINGLE,     /* ' */
	TOKEN_SEMICOLON,        /* ; */
	TOKEN_SLASH_BACKWARD,   /* \ */
	TOKEN_SLASH_FORWARD,    /* / */

	// Atoms
	TOKEN_NUMBER, /* 0-9 */
	TOKEN_SYMBOL,
};

struct token {
	enum token_type type;
	size_t index;
	char const *data;
	struct token *next;
	struct token *tail;
};

struct token *new_token(enum token_type type, size_t index, char const *data);

struct token *token_append(struct token *tokens, struct token *token);

#endif // PLOY_READER_TOKEN_H
