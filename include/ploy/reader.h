// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_READER_H
#pragma once

#include <ploy/ploy.h>
#include <ploy/reader/lexer.h>
#include <ploy/reader/parser.h>
#include <ploy/reader/token.h>

struct object *reader(const char *input);

#endif // PLOY_READER_H
