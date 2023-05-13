// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_LEXER_H
#pragma once

#include <ploy/reader/token.h>

struct token const *lexer(char const *input);

char lexer_peek(char const *input);

struct token *lex_number(size_t *index, char const **input);
struct token *lex_symbol(size_t *index, char const **input);

#endif // PLOY_READER_LEXER_H
