// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_LEXER_H
#pragma once

#include <ploy/reader/token.h>

Token *lexer(const char *input);

char lexer_peek(const char *input);

struct token *lex_comment(size_t *index, const char **input);
struct token *lex_keyword(size_t *index, const char **input);
struct token *lex_number(size_t *index, const char **input);
struct token *lex_string(size_t *index, const char **input);
struct token *lex_symbol(size_t *index, const char **input);
struct token *lex_token(size_t *index, const char **input, size_t length);

#endif // PLOY_READER_LEXER_H
