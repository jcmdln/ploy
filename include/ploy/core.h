// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_CORE_H
#define PLOY_CORE_H
#pragma once

#include "type.h"

Object const *Append(Object const *target, Object const *object);
// Object const *Apply(Object const *object);
Object const *Car(Object const *object);
Object const *Cdr(Object const *object);
Object const *Cons(Object const *car, Object const *cdr);
// Object const *Define(Object const *env, Object const *symbol, Object const *value);
Object const *Eval(Object const *object);
// Object const *For(Object const *expr, Object const *body);
// Object const *If(Object const *expr, Object const *body);
// Object const *Lambda(Object const *env, Object const *args, Object const *body);
// Object const *Let(Object const *env, Object const *args, Object const *body);
Object const *Print(Object const *object);
// Object const *Quasiquote(Object const *object);
// Object const *Quote(Object const *object);
Object const *Read(char const *input);
Object const *Reverse(Object const *object);

#endif // PLOY_CORE_H
