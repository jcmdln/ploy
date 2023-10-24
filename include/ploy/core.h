#pragma once

#include "type.h"

static Object *Nil = &(Object){ .type = NIL };
static Object *True = &(Object){ .type = NIL, .boolean = true };
static Object *False = &(Object){ .type = NIL, .boolean = false };

Object *Append(Object *target, Object *object);
Object *Apply(Object *object);
Object *Assert(bool condition);
Object *Car(Object *object);
Object *Cdr(Object *object);
Object *Cons(Object *car, Object *cdr);
Object *Define(Object *env, Object *args, Object *body);
Object *Error(char *error);
Object *Eval(Object *object);
Object *For(Object *expr, Object *body);
Object *Format(char *form, ...);
Object *If(Object *expr, Object *body);
Object *Lambda(Object *env, Object *args, Object *body);
Object *Let(Object *env, Object *args, Object *body);
Object *Print(Object *object);
Object *Read(char *input);
Object *Reverse(Object *object);

Object *Number(int64_t i64);
Object *String(char *string);
Object *Symbol(char *symbol);
