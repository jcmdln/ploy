// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdlib.h>

#include <gc/gc.h>

#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/reader.h>
#include <ploy/reader/token.h>

Object const *
reader(char const *const input)
{
	if (!input) return Error("reader: input is NULL");

	Token const *const tokens = lexer(input);
	if (!tokens) return Error("reader: tokens is NULL");
	if (tokens->type == TOKEN_ERROR) return Error(tokens->data);

	return parser(tokens);
}
