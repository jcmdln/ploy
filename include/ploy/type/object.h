// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_TYPE_OBJECT_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <ploy/type/lambda.h>
#include <ploy/type/list.h>

enum object_type {
	OBJECT_NIL = 0,
	OBJECT_BOOLEAN,
	OBJECT_ERROR,
	OBJECT_KEYWORD,
	OBJECT_LAMBDA,
	OBJECT_LIST,
	OBJECT_NUMBER,
	OBJECT_STRING,
	OBJECT_SYMBOL,
};

struct object {
	enum object_type type;
	union {
		bool boolean;
		const char *error;
		char *keyword;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
		char *string;
		char *symbol;
	};
};

struct object *object_boolean(bool boolean);
struct object *object_error(const char *error);
struct object *object_keyword(char *keyword);
struct object *object_lambda(struct lambda *lambda);
struct object *object_list(struct list *list);
struct object *object_nil(void);
struct object *object_number(int64_t number);
struct object *object_string(char *string);
struct object *object_symbol(char *symbol);

#endif // PLOY_TYPE_OBJECT_H
