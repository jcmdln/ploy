#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy/core.h>

static char TOKENS[11] = " \n\r\t\v;()\"\0";

Object *read_delimiters(char *input, char begin, char end);
Object *read_form(size_t *index, char **input);
Object *read_list(size_t *index, char **input);
Object *read_number(size_t *index, char **input);
Object *read_string(size_t *index, char **input);
Object *read_symbol(size_t *index, char **input);

Object *
reader(char *input)
{
	if (!input) return Error("reader: input is NULL");

	Object *delims = read_delimiters(input, '(', ')');
	if (delims->type != NIL) return delims;

	size_t index = 0;
	Object *forms = read_form(&index, &input);
	if (forms->type == ERROR) return forms;

	return Reverse(forms);
}

Object *
read_delimiters(char *input, char begin, char end)
{
	if (!input) return Error("read_delimiters: input is NULL");

	char *cursor = input;
	int64_t balanced = 0;

	while (*cursor) {
		if (*cursor == begin)
			++balanced;
		else if (*cursor == end)
			--balanced;
		++cursor;
	}

	if (balanced < 0) return Error("read_delimiters: missing begin");
	if (balanced > 0) return Error("read_delimiters: missing end");

	return Nil;
}

Object *
read_form(size_t *index, char **input)
{
	if (!index) return Error("read_form: Index is NULL");
	if (!input) return Error("read_form: input is NULL");

	char *cursor = *input;
	size_t length = *index;
	Object *objects = Nil;

	while (*cursor) {
		Object *object = Nil;

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
			object = Nil;
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
		if (object->type == ERROR) return object;

		objects = Cons(object, objects);
		if (object->type == NIL) break;
	}

	*input = cursor;

	return objects;
}

Object *
read_list(size_t *index, char **input)
{
	if (!index) return Error("read_list: Index is NULL");
	if (!input) return Error("read_list: input is NULL");

	char *cursor = *input;
	size_t length = 0;

	if (*cursor != '(') return Error("read_list: missing open parenthesis `(`");
	cursor = ++*input;
	length = *index;

	Object *object = read_form(&length, &cursor);
	if (*cursor != ')') return Error("read_list: missing close parenthesis `)`");
	*input = ++cursor;

	return object;
}

Object *
read_number(size_t *index, char **input)
{
	if (!index) return Error("read_number: Index is NULL");
	if (!input) return Error("read_number: input is NULL");

	char *cursor = *input;
	size_t length = 0;

	if (*cursor == '+' || *cursor == '-') {
		++cursor;
		++length;
	}

	while (isdigit(*cursor)) {
		++cursor;
		++length;
	}

	char *number = GC_MALLOC(length + 1);
	memcpy(number, *input, length);
	number[length] = '\0';

	Object *obj = Number(strtoll(number, NULL, 10));
	GC_FREE(number);

	*input = cursor;
	*index += length;
	return obj;
}

Object *
read_string(size_t *index, char **input)
{
	if (!index) return Error("read_string: Index is NULL");
	if (!input) return Error("read_string: input is NULL");

	char *cursor = *input;
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

	char *string = GC_MALLOC(length + 1);
	memcpy(string, *input, length);
	string[length] = '\0';

	*input = cursor;
	*index += ++length;
	return String(string);
}

Object *
read_symbol(size_t *index, char **input)
{
	if (!index) return Error("read_symbol: Index is NULL");
	if (!input) return Error("read_symbol: input is NULL");

	char *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}
	if (length == 0) return Error("read_symbol: invalid length 0");

	char *symbol = GC_MALLOC(length + 1);
	memcpy(symbol, *input, length);
	symbol[length] = '\0';

	*input = cursor;
	*index += length;
	return Symbol(symbol);
}
