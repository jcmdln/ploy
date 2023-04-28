// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_LEXER_H
#pragma once

#include <ploy/reader/token.h>

const struct token *lexer(const char *input);

char lexer_peek(const char *input);

struct token *lex_number(size_t *index, const char **input);
struct token *lex_symbol(size_t *index, const char **input);

#endif // PLOY_READER_LEXER_H
