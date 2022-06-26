// SPDX-License-Identifier: ISC

#include <stdint.h>
#include <stdlib.h>

#include <gc.h>
#include <string.h>

#include "string.h"

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
