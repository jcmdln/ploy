// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/reader/token.h>
#include <ploy/type.h>

const struct object *parser(Token *token);

const struct object *parse_form(Token **tokens);

const struct object *parse_comment(Token **tokens);
const struct object *parse_keyword(Token **token);
const struct object *parse_lambda(Token **token);
const struct object *parse_list(Token **token);
const struct object *parse_number(Token **token);
const struct object *parse_quasiquote(Token **token);
const struct object *parse_quote(Token **token);
const struct object *parse_string(Token **token);
const struct object *parse_symbol(Token **token);

#endif // PLOY_READER_PARSER_H
