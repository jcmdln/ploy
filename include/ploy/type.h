#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct object Object;
struct object {
	enum {
		NIL = 0,
		BOOLEAN,
		ERROR,
		// LAMBDA,
		LIST,
		STRING,
		SYMBOL,

		// F64,
		I64,
		// U64,
	} type;
	union {
		bool boolean;
		struct /* lambda */ {
			Object *args, *body;
		};
		struct /* list */ {
			Object *car, *cdr;
		};
		char *string;

		double_t f64;
		int64_t i64;
		uint64_t u64;
	};
};
