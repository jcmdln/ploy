// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_BUILTINS_H
#pragma once

#include <ploy/type/object.h>

struct object *Append(struct object *list, struct object *object);
struct object *Car(struct object *list);
struct object *Cdr(struct object *list);
struct object *Cons(struct object *car, struct object *cdr);
struct object *Define(struct object *env, struct object *symbol, struct object *value);
struct object *Eval(struct object *object);
struct object *For(struct object *expr, struct object *body);
struct object *If(struct object *expr, struct object *body);
struct object *Lambda(struct object *env, struct object *args, struct object *body);
struct object *Print(struct object *object);
struct object *Quasiquote(struct object *object);
struct object *Quote(struct object *object);
struct object *Read(const char *input);
struct object *Reverse(struct object *object);

#endif // PLOY_BUILTINS_H
