#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct Object {
	enum { NIL = 0, BOOLEAN, ERROR, LAMBDA, LIST, NUMBER, STRING, SYMBOL } type;
	union { // clang-format off
		bool boolean;
		int64_t number;
		char const *error, *string, *symbol;
		struct { struct Object *args, *body; } *lambda;
		struct { struct Object *element, *next; } *list;
	}; // clang-format on
} Object;

//
// Core
//

static Object *const Nil = &(Object){ .type = NIL };
static Object *const True = &(Object){ .type = NIL, .boolean = true };
static Object *const False = &(Object){ .type = NIL, .boolean = false };

Object *Append(Object *target, Object *object);
Object *Apply(Object *object);
Object *Car(Object *object);
Object *Cdr(Object *object);
Object *Cons(Object *car, Object *cdr);
Object *Define(Object *env, Object *args, Object *body);
Object *Error(char const *error);
Object *Eval(Object *object);
Object *For(Object *expr, Object *body);
Object *If(Object *expr, Object *body);
Object *Lambda(Object *args, Object *body);
Object *Let(Object *env, Object *args, Object *body);
Object *Number(int64_t number);
Object *Print(Object *object);
Object *Read(char const *input);
Object *Reverse(Object *object);
Object *String(char const *string);

//
// Math
//

Object *Add(Object *object);
Object *Subtract(Object *object);
Object *Multiply(Object *object);
Object *Divide(Object *object);

// Object *Exponent(Object *object);
// Object *Log(Object *object);
// Object *Modulo(Object *object);
// Object *NthRoot(Object *object, int64_t nth);
