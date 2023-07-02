// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_LEXER_H
#pragma once

#include <ploy/reader/token.h>

Token const *lexer(char const *input);

char lexer_peek(char const *input);

Token *lex_number(size_t *index, char const **input);
Token *lex_symbol(size_t *index, char const **input);
Token *lex_token(TokenType type, char const **cursor, size_t *index, char const *data);

#endif // PLOY_READER_LEXER_H
