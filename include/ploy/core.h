// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_CORE_H
#pragma once

#include <ploy/type.h>

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

#endif // PLOY_CORE_H
