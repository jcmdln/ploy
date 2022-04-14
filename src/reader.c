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
	struct object *obj = NULL;

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
			obj = object_new_list(read_keyword(&cursor), obj);
			break;

		// list
		case '(':
			obj = object_new_list(read_list(&cursor), obj);
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
			obj = object_new_list(read_number(&cursor), obj);
			break;

		// quote
		case '\'':
		// quasiquote
		case '`':
			++cursor;
			obj = object_new_list(read_quote(&cursor), obj);
			break;

		// string
		case '"':
			++cursor;
			obj = object_new_list(read_string(&cursor), obj);
			break;

		// symbol
		default:
			obj = object_new_list(read_symbol(&cursor), obj);
			break;
		}
	};

	*input = cursor;

	return obj;
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
