// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/ploy.h>
#include <ploy/reader/token.h>

Object const *parser(Token const *token);

Object const *parse_form(Token const **tokens);

Object const *parse_comment(Token const **tokens);
Object const *parse_keyword(Token const **token);
Object const *parse_lambda(Token const **token);
Object const *parse_list(Token const **token);
Object const *parse_number(Token const **token);
Object const *parse_quasiquote(Token const **token);
Object const *parse_quote(Token const **token);
Object const *parse_string(Token const **token);
Object const *parse_symbol(Token const **token);

#endif // PLOY_READER_PARSER_H
