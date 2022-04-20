// SPDX-License-Identifier: ISC

#include <stdint.h>
#include <stdlib.h>

#include <gc.h>
#include <string.h>

#include "string.h"

struct string *
string_append(struct string *dest, char *str)
{
	if (!dest || !str) {
		return NULL;
	}

	return dest;
}

struct string *
string_copy(struct string *string)
{
	return string;
}

struct string *
string_join(struct string *dest, struct string *src)
{
	struct string *string = NULL;

	if (!dest || !src) {
		return NULL;
	}

	return string;
}

struct number *
string_length(struct string *string)
{
	struct number *number = NULL;

	if (string) {
	}

	return number;
}

struct string *
string_new(char *src)
{
	struct string *string = (struct string *)GC_MALLOC(sizeof(*string));

	string->length = strlen(src);
	if (string->length > INT64_MAX) {
		return NULL;
	}

	string->data = (char *)GC_MALLOC(string->length + 1);
	string->data = src;

	return string;
}

struct string *
string_slice(struct string *string, int64_t offset, int64_t length)
{
	if (offset == 0 || length == 0) {
		return string;
	}

	return string;
}

struct string *
string_sort(struct string *string)
{
	return string;
}

struct number *
string_to_number(struct string *string)
{
	struct number *number = 0;

	if (string) {
	}

	return number;
}
