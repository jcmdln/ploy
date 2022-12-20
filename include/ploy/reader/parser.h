// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/ploy.h>
#include <ploy/reader/token.h>

struct object *parser(struct token *token);

struct object *parse_form(struct token **tokens);
struct object *parse_keyword(struct token **token);
struct object *parse_lambda(struct token **token);
struct object *parse_list(struct token **token);
struct object *parse_number(struct token **token);
struct object *parse_quasiquote(struct token **token);
struct object *parse_quote(struct token **token);
struct object *parse_string(struct token **token);
struct object *parse_symbol(struct token **token);

#endif // PLOY_READER_PARSER_H
