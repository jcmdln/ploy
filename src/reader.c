// SPDX-License-Identifier: ISC

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "reader.h"

struct object *
reader(char **input)
{
	char *cursor = *input;
	struct list *list = list_new(NULL, NULL);

	while (*cursor) {
		switch (*cursor) {
		// whitespace
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			++cursor;
			break;

		// comment
		case '#':
			while (*++cursor) {
				switch (*cursor) {
				case '\n':
				case '\0':
				case EOF:
					break;
				};
			}
			break;

		// keyword
		case ':':
			++cursor;
			list_append(list, read_keyword(&cursor));
			break;

		// list
		case '(':
			list_append(list, read_list(&cursor));
			break;
		case ')':
			++cursor;
			break;

		// number sign
		// case '+':
		// case '-':
		//	if (isdigit(cur[1])) {
		//		cur = read_number(&cur);
		//		break;
		//	}
		//	break;

		// number
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			list_append(list, read_number(&cursor));
			break;

		// quote
		case '\'':
		// quasiquote
		case '`':
			++cursor;
			list_append(list, read_quote(&cursor));
			break;

		// string
		case '"':
			++cursor;
			list_append(list, read_string(&cursor));
			break;

		// symbol
		default:
			list_append(list, read_symbol(&cursor));
			break;
		}
	};

	*input = cursor;

	return object_new_list(list);
}

struct object *
read_keyword(char **input)
{
	char *cursor = *input;
	int64_t position = 0;

	while (*cursor) {
		switch (*cursor) {
		case ' ':
		case ')':
			break;

		default:
			++cursor;
			++position;
			continue;
		}

		break;
	}

	struct object *obj = object_new_keyword(strndup(*input, position));
	*input = cursor;

	return obj;
}

struct object *
read_list(char **input)
{
	char *cursor = *input;
	struct object *obj = NULL;

	while (*cursor) {
		switch (*cursor) {
		case '\0':
			fputs("error: reader: no matching ')'", stderr);
			exit(1);

		case '(':
			++cursor;
			obj = reader(&cursor);
			break;
		}
	}

	*input = cursor;

	return obj;
}

struct object *
read_number(char **input)
{
	char *cursor = *input;
	int64_t position = 0;

	while (*cursor) {
		switch (*cursor) {
		case ' ':
		case ')':
			break;

		default:
			++cursor;
			++position;
			continue;
		}

		break;
	}

	struct object *obj = object_new_number(atoi(strndup(*input, position)));
	*input = cursor;

	return obj;
}

struct object *
read_quote(char **input)
{
	char *cursor = *input;
	int64_t position = 0;

	while (*cursor) {
		switch (*cursor) {
		case ' ':
		case ')':
			break;

		default:
			++cursor;
			++position;
			continue;
		}

		break;
	}

	struct object *obj = object_new_symbol(strndup(*input, position));
	*input = cursor;

	return obj;
}

struct object *
read_string(char **input)
{
	char *cursor = *input;
	int64_t position = 0;

	while (*cursor && *cursor != '\"') {
		++cursor;
		++position;
	}

	if (*cursor != '\"') {
		fputs("error: reader: no matching '\"'", stderr);
		exit(1);
	}

	struct object *obj = object_new_string(strndup(*input, position));
	*input = ++cursor;

	return obj;
}

struct object *
read_symbol(char **input)
{
	char *cursor = *input;
	int64_t position = 0;

	while (*cursor) {
		switch (*cursor) {
		case ' ':
		case ')':
			break;

		default:
			++cursor;
			++position;
			continue;
		}

		break;
	}

	struct object *obj = object_new_symbol(strndup(*input, position));
	*input = cursor;

	return obj;
}
