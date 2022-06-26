// SPDX-License-Identifier: ISC

#ifndef PLOY_TYPES_STRING_H
#pragma once

#include <stdbool.h>
#include <stdint.h>

struct string {
	char *data;
	int64_t length;
};

// struct string *string_append(struct string *str, char *);
// struct string *string_copy(struct string *str);
// struct number *string_length(struct string *str);
struct string *string_new(char *);
// struct string *string_slice(struct string *str, int64_t, int64_t);
// struct string *string_sort(struct string *str);
// struct number *string_to_number(struct string *);

#endif // PLOY_TYPES_STRING_H
