// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_TOKEN_H
#pragma once

#include <sys/types.h>

static char const TOKENS[24] = "\r\n \t\v*`^:=><-#()%+\"\';\\/\0";

typedef enum TokenType {
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
	TOKEN_STRING,
	TOKEN_SYMBOL,
} TokenType;

typedef struct Token {
	TokenType type;
	char const *data;
	struct Token *next;
	struct Token *tail;
} Token;

Token *token_init(TokenType type, char const *data);
void token_free(Token *token);

Token *token_append(Token *tokens, Token *token);

#endif // PLOY_READER_TOKEN_H
