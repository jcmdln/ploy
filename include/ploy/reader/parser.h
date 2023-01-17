// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/ploy.h>
#include <ploy/reader/token.h>

Object *parser(Token *token);

Object *parse_form(Token **tokens);
Object *parse_keyword(Token **token);
Object *parse_lambda(Token **token);
Object *parse_list(Token **token);
Object *parse_number(Token **token);
Object *parse_quasiquote(Token **token);
Object *parse_quote(Token **token);
Object *parse_string(Token **token);
Object *parse_symbol(Token **token);

#endif // PLOY_READER_PARSER_H
