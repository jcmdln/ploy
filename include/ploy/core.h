// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_CORE_H
#pragma once

#include <ploy/type.h>

// Constants
static const struct object Nil = { .type = OBJECT_NIL };
static const struct object False = { .type = OBJECT_BOOLEAN, .boolean = false };
static const struct object True = { .type = OBJECT_BOOLEAN, .boolean = true };

// Core
const struct object *Append(const struct object *list, const struct object *object);
const struct object *Apply(const struct object *object);
const struct object *Car(const struct object *object);
const struct object *Cdr(const struct object *object);
const struct object *Cons(const struct object *car, const struct object *cdr);
const struct object *Define(const struct object *env, const struct object *symbol,
	const struct object *value);
const struct object *Error(const char *error);
const struct object *Eval(const struct object *object);
const struct object *For(const struct object *expr, const struct object *body);
const struct object *If(const struct object *expr, const struct object *body);
const struct object *Lambda(const struct object *env, const struct object *args,
	const struct object *body);
const struct object *Print(const struct object *object);
const struct object *Quasiquote(const struct object *object);
const struct object *Quote(const struct object *object);
const struct object *Read(const char *input);
const struct object *Reverse(const struct object *object);

#endif // PLOY_CORE_H
