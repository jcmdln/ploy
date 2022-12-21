// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_H
#pragma once

#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>
#include <ploy/type.h>

struct object *reader(const char *input);

struct object *read_list_delimiters(struct token *tokens);

#endif // PLOY_READER_H
