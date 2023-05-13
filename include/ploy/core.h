// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_CORE_H
#pragma once

#include <ploy/type.h>

// Constants
static struct object const Nil = { .type = OBJECT_NIL };
static struct object const False = { .type = OBJECT_BOOLEAN, .boolean = false };
static struct object const True = { .type = OBJECT_BOOLEAN, .boolean = true };

// Core
struct object const *Append(struct object const *list, struct object const *object);
struct object const *Apply(struct object const *object);
struct object const *Car(struct object const *object);
struct object const *Cdr(struct object const *object);
struct object const *Cons(struct object const *car, struct object const *cdr);
struct object const *Define(struct object const *env, struct object const *symbol,
	struct object const *value);
struct object const *Error(char const *error);
struct object const *Eval(struct object const *object);
struct object const *For(struct object const *expr, struct object const *body);
struct object const *If(struct object const *expr, struct object const *body);
struct object const *Lambda(struct object const *env, struct object const *args,
	struct object const *body);
struct object const *Print(struct object const *object);
struct object const *Quasiquote(struct object const *object);
struct object const *Quote(struct object const *object);
struct object const *Read(char const *input);
struct object const *Reverse(struct object const *object);

#endif // PLOY_CORE_H
