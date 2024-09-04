#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct Ploy Ploy;
struct Ploy {
	enum {
		PloyNIL = 0,
		PloyBOOLEAN,
		PloyERROR,
		PloyLAMBDA,
		PloyLIST,
		PloyNUMBER,
		PloySTRING,
		PloySYMBOL
	} type;
	union { // clang-format off
		bool boolean;
		char const *error;
		struct { Ploy *args, *body; } *lambda;
		struct { Ploy *element, *next; } *list;
		int64_t number;
		char const *string;
		char const *symbol;
	}; // clang-format on
};

//
// Core
//

static Ploy *const PloyNil = &(Ploy){ .type = PloyNIL };
static Ploy *const PloyTrue = &(Ploy){ .type = PloyBOOLEAN, .boolean = true };
static Ploy *const PloyFalse = &(Ploy){ .type = PloyBOOLEAN, .boolean = false };

Ploy *PloyAppend(Ploy *target, Ploy *object);
Ploy *PloyApply(Ploy *object);
Ploy *PloyCar(Ploy *object);
Ploy *PloyCdr(Ploy *object);
Ploy *PloyCons(Ploy *car, Ploy *cdr);
Ploy *PloyDefine(Ploy *env, Ploy *args, Ploy *body);
Ploy *PloyError(char const *error);
Ploy *PloyEval(Ploy *object);
Ploy *PloyFor(Ploy *expr, Ploy *body);
Ploy *PloyIf(Ploy *expr, Ploy *body);
Ploy *PloyLambda(Ploy *args, Ploy *body);
Ploy *PloyLet(Ploy *env, Ploy *args, Ploy *body);
Ploy *PloyNumber(int64_t number);
Ploy *PloyPrint(Ploy *object);
Ploy *PloyRead(char const *input);
Ploy *PloyReverse(Ploy *object);
Ploy *PloyString(char const *string);

//
// Math
//

Ploy *PloyAdd(Ploy *object);
Ploy *PloySubtract(Ploy *object);
Ploy *PloyMultiply(Ploy *object);
Ploy *PloyDivide(Ploy *object);

// Ploy *PloyExponent(Ploy *object);
// Ploy *PloyLog(Ploy *object);
// Ploy *PloyModulo(Ploy *object);
// Ploy *PloyNthRoot(Ploy *object, int64_t nth);
