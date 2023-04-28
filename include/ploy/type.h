// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_TYPE_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

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

typedef struct object {
	enum object_type type;
	union {
		const char *atom;
		bool boolean;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
	};
} const Object;

struct lambda {
	Object *env;
	Object *args;
	Object *body;
};

struct list {
	Object *car;
	Object *cdr;
};

#endif // PLOY_TYPE_H
