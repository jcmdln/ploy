// SPDX-License-Identifier: ISC

#ifndef TYPES_STRING_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

struct string {
	char *data;
	int64_t length;
};

struct string *string_append(struct string *, char *);
struct string *string_copy(struct string *);
struct number *string_length(struct string *);
struct string *string_join(struct string *, struct string *);
struct string *string_new(char *);
struct string *string_slice(struct string *, int64_t, int64_t);
struct string *string_sort(struct string *);
struct number *string_to_number(struct string *);

#endif // TYPES_STRING_H
