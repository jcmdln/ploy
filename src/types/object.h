// SPDX-License-Identifier: ISC

#ifndef TYPES_OBJECT_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

enum object_t {
	nil_t = 0,
	boolean_t,
	error_t,
	keyword_t,
	lambda_t,
	list_t,
	number_t,
	string_t,
	symbol_t,
};

struct object {
	enum object_t type;
	struct {
		bool boolean;
		char *error;
		char *keyword;
		struct lambda *lambda;
		struct list *list;
		int64_t number;
		char *string;
		char *symbol;
	};
};

struct object *object_new(enum object_t);
struct object *object_new_boolean(bool);
struct object *object_new_error(char *);
struct object *object_new_keyword(char *);
struct object *object_new_lambda(struct object *, struct object *, struct object *);
struct object *object_new_list(struct list *);
struct object *object_new_number(int64_t);
struct object *object_new_string(char *);
struct object *object_new_symbol(char *);
char *object_typename(enum object_t);

#endif // TYPES_OBJECT_H
