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

// Constants
static Object Nil = { .type = OBJECT_NIL };
static Object False = { .type = OBJECT_BOOLEAN, .boolean = false };
static Object True = { .type = OBJECT_BOOLEAN, .boolean = true };

// Core
Object *Append(Object *list, Object *object);
Object *Apply(Object *object);
Object *Car(Object *object);
Object *Cdr(Object *object);
Object *Cons(Object *car, Object *cdr);
Object *Define(Object *env, Object *symbol, Object *value);
Object *Error(const char *error);
Object *Eval(Object *object);
Object *For(Object *expr, Object *body);
Object *If(Object *expr, Object *body);
Object *Lambda(Object *env, Object *args, Object *body);
Object *Print(Object *object);
Object *Quasiquote(Object *object);
Object *Quote(Object *object);
Object *Read(const char *input);
Object *Reverse(Object *object);

#endif // PLOY_H
