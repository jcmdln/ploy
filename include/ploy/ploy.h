// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_H
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

struct lambda {
	struct object *env;
	struct object *args;
	struct object *body;
};

struct list {
	struct object *car;
	struct object *cdr;
};

struct object {
	enum object_type type;
	union {
		bool boolean;
		const char *error;
		const char *keyword;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
		const char *string;
		const char *symbol;
	};
};

// Constants
static struct object Nil = { .type = OBJECT_NIL };
static struct object False = { .type = OBJECT_BOOLEAN, .boolean = false };
static struct object True = { .type = OBJECT_BOOLEAN, .boolean = true };

// Core
struct object *Append(struct object *list, struct object *object);
struct object *Apply(struct object *object);
struct object *Car(struct object *object);
struct object *Cdr(struct object *object);
struct object *Cons(struct object *car, struct object *cdr);
struct object *Define(struct object *env, struct object *symbol, struct object *value);
struct object *Error(const char *error);
struct object *Eval(struct object *object);
struct object *For(struct object *expr, struct object *body);
struct object *If(struct object *expr, struct object *body);
struct object *Lambda(struct object *env, struct object *args, struct object *body);
struct object *Print(struct object *object);
struct object *Quasiquote(struct object *object);
struct object *Quote(struct object *object);
struct object *Read(const char *input);
struct object *Reverse(struct object *object);

#endif // PLOY_H
