// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_H
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum ObjectType {
	OBJECT_NIL = 0,
	OBJECT_BOOLEAN,
	OBJECT_ERROR,
	OBJECT_KEYWORD,
	OBJECT_LAMBDA,
	OBJECT_LIST,
	OBJECT_NUMBER,
	OBJECT_STRING,
	OBJECT_SYMBOL,
} ObjectType;

typedef struct Object {
	ObjectType type;
	union {
		bool boolean;
		char const *error;
		char const *keyword;
		struct {
			struct Object const *args, *body;
		} *lambda;
		struct {
			struct Object const *car, *cdr, *tail;
		} *list;
		int64_t number;
		char const *string;
		char const *symbol;
	};
} Object;

// Constants
static Object const Nil = { .type = OBJECT_NIL };
static Object const False = { .type = OBJECT_BOOLEAN, .boolean = false };
static Object const True = { .type = OBJECT_BOOLEAN, .boolean = true };

// Core
Object const *Append(Object const *target, Object const *object);
Object const *Apply(Object const *object);
Object const *Car(Object const *object);
Object const *Cdr(Object const *object);
Object const *Cons(Object const *car, Object const *cdr);
Object const *Define(Object const *env, Object const *symbol, Object const *value);
Object const *Error(char const *error);
Object const *Eval(Object const *object);
Object const *For(Object const *expr, Object const *body);
Object const *If(Object const *expr, Object const *body);
Object const *Lambda(Object const *env, Object const *args, Object const *body);
Object const *Print(Object const *object);
Object const *Quasiquote(Object const *object);
Object const *Quote(Object const *object);
Object const *Read(char const *input);
Object const *Reverse(Object const *object);

#endif // PLOY_H
