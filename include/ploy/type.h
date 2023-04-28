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
		const char *atom;
		bool boolean;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
	};
};

struct lambda {
	const struct object *env;
	const struct object *args;
	const struct object *body;
};

struct list {
	const struct object *car;
	const struct object *cdr;
};

#endif // PLOY_TYPE_H
