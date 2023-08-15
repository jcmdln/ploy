// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_TYPE_H
#define PLOY_TYPE_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum Type {
	TYPE_NIL = 0,
	TYPE_BOOLEAN,
	TYPE_ERROR,
	// TYPE_LAMBDA,
	TYPE_LIST,
	TYPE_NUMBER,
	TYPE_STRING,
	TYPE_SYMBOL,
} Type;

// struct Lambda {
// 	struct Object const *args, *body;
// };

struct List {
	struct Object const *car, *cdr;
};

typedef struct Object {
	Type type;
	union {
		bool boolean;
		// struct Lambda *lambda;
		struct List *list;
		int64_t number;
		char const *string;
	};
} Object;

static Object const NIL = { .type = TYPE_NIL };

Object *Boolean(bool boolean);
Object *Error(char const *error);
Object *Number(int64_t number);
Object *String(char const *string);
Object *Symbol(char const *symbol);

#endif // PLOY_TYPE_H
