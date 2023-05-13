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

struct object {
	enum object_type type;
	union {
		char const *atom;
		bool boolean;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
	};
};

struct lambda {
	struct object const *env;
	struct object const *args;
	struct object const *body;
};

struct list {
	struct object const *car;
	struct object const *cdr;
	struct object const *tail;
};

#endif // PLOY_TYPE_H
