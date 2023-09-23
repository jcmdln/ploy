// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/core.h>

static char const TOKENS[11] = " \n\r\t\v;()\"\0";

Object const *read_delimiters(char const *input, char begin, char end);
Object const *read_form(size_t const *index, char const **input);
Object const *read_list(size_t const *index, char const **input);
Object const *read_number(size_t *index, char const **input);
Object const *read_string(size_t *index, char const **input);
Object const *read_symbol(size_t *index, char const **input);

Object const *
reader(char const *input)
{
	if (!input) return Error("reader: input is NULL");

	Object const *const delims = read_delimiters(input, '(', ')');
	if (delims->type != TYPE_NIL) return delims;

	size_t index = 0;
	Object const *forms = read_form(&index, &input);
	if (forms->type == TYPE_ERROR) return forms;

	return Reverse(forms);
}

Object const *
read_delimiters(char const *const input, char const begin, char const end)
{
	char const *cursor = input;
	int64_t balanced = 0;

	do {
		if (*cursor == begin) {
			++balanced;
		} else if (*cursor == end) {
			--balanced;
		}
	} while (*++cursor);

	if (balanced < 0) return Error("read_delimiters: missing begin");
	if (balanced > 0) return Error("read_delimiters: missing end");

	return &NIL;
}

Object const *
read_form(size_t const *index, char const **const input)
{
	if (!input) return Error("reader: input is NULL");

	char const *cursor = *input;
	size_t length = *index;
	Object const *objects = &NIL;

	while (*cursor) {
		Object const *object = &NIL;

		switch (*cursor) {
		// Whitespace
		case ' ':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			++cursor;
			++length;
			continue;

		// Comment
		case ';':
		case '#':
			while (*cursor && *++cursor != '\n')
				++length;
			continue;

		// List
		case ')':
			object = &NIL;
			break;
		case '(':
			object = read_list(&length, &cursor);
			break;

		// Number
		case '-':
		case '+':
			if (isdigit(cursor[1]))
				object = read_number(&length, &cursor);
			else
				object = read_symbol(&length, &cursor);
			break;
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
			object = read_number(&length, &cursor);
			break;

		// String
		case '\"':
			object = read_string(&length, &cursor);
			break;

		// Symbol
		default:
			object = read_symbol(&length, &cursor);
		}

		if (!object) return Error("read_form: object is NULL");
		if (object->type == TYPE_ERROR) return object;

		objects = Cons(object, objects);
		if (object->type == TYPE_NIL) break;
	}

	*input = cursor;

	return objects;
}

Object const *
read_list(size_t const *const index, char const **const input)
{
	char const *cursor = *input;
	size_t length = 0;

	if (*cursor != '(') return Error("read_list: missing open parenthesis `(`");
	cursor = ++*input;
	length = *index;

	Object const *object = read_form(&length, &cursor);
	if (*cursor != ')') return Error("read_list: missing close parenthesis `)`");
	*input = ++cursor;

	return object;
}

Object const *
read_number(size_t *const index, char const **const input)
{
	char const *cursor = *input;
	size_t length = 0;

	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (isdigit(*cursor)) {
		++cursor;
		++length;
	}

	char *const number = GC_MALLOC(length + 1);
	memcpy(number, *input, length);
	number[length] = '\0';

	Object *const object = Number(strtoll(number, NULL, 10));
	GC_FREE(number);

	*input = cursor;
	*index += length;
	return object;
}

Object const *
read_string(size_t *const index, char const **const input)
{
	char const *cursor = *input;
	size_t length = 0;

	if (*cursor != '\"') return Error("read_string: Missing open '\"'");
	cursor = ++*input;
	*index += 1;

	while (*cursor && *cursor != '\"') {
		++cursor;
		++length;
	}

	if (*cursor != '\"') return Error("read_string: Missing close '\"'");
	++cursor;

	char *const string = GC_MALLOC(length + 1);
	memcpy(string, *input, length);
	string[length] = '\0';

	*input = cursor;
	*index += ++length;
	return String(string);
}

Object const *
read_symbol(size_t *const index, char const **const input)
{
	char const *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}
	if (length == 0) return Error("read_symbol: invalid length 0");

	char *const symbol = GC_MALLOC(length + 1);
	memcpy(symbol, *input, length);
	symbol[length] = '\0';

	*input = cursor;
	*index += length;
	return Symbol(symbol);
}
