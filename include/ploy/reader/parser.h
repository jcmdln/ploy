// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/reader/token.h>
#include <ploy/type.h>

struct object const *parser(struct token const *token);

struct object const *parse_form(struct token const **tokens);

struct object const *parse_comment(struct token const **tokens);
struct object const *parse_keyword(struct token const **token);
struct object const *parse_lambda(struct token const **token);
struct object const *parse_list(struct token const **token);
struct object const *parse_number(struct token const **token);
struct object const *parse_quasiquote(struct token const **token);
struct object const *parse_quote(struct token const **token);
struct object const *parse_string(struct token const **token);
struct object const *parse_symbol(struct token const **token);

#endif // PLOY_READER_PARSER_H
