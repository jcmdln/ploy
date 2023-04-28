// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_PARSER_H
#pragma once

#include <ploy/reader/token.h>
#include <ploy/type.h>

const struct object *parser(const struct token *token);

const struct object *parse_form(const struct token **tokens);

const struct object *parse_comment(const struct token **tokens);
const struct object *parse_keyword(const struct token **token);
const struct object *parse_lambda(const struct token **token);
const struct object *parse_list(const struct token **token);
const struct object *parse_number(const struct token **token);
const struct object *parse_quasiquote(const struct token **token);
const struct object *parse_quote(const struct token **token);
const struct object *parse_string(const struct token **token);
const struct object *parse_symbol(const struct token **token);

#endif // PLOY_READER_PARSER_H
