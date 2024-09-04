#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <gc/gc.h>

#include <ploy.h>

static char TOKENS[11] = " \n\r\t\v#;()\"\0";

Ploy *read_delimiters(char const *input, char begin, char end);
Ploy *read_form(size_t *index, char const **input);
Ploy *read_list(size_t *index, char const **input);
Ploy *read_number(size_t *index, char const **input);
Ploy *read_string(size_t *index, char const **input);
Ploy *read_symbol(size_t *index, char const **input);

// TODO: jcmdln: non-recursive `Read`
Ploy *
PloyRead(char const *input)
{
	if (!input) return PloyError("Read: input is NULL");

	Ploy *delims = read_delimiters(input, '(', ')');
	if (delims->type != PloyNIL) return delims;

	size_t index = 0;
	Ploy *forms = read_form(&index, &input);
	if (forms->type == PloyERROR) return forms;

	return PloyReverse(forms);
}

Ploy *
read_delimiters(char const *const input, char begin, char end)
{
	if (!input) return PloyError("read_delimiters: input is NULL");

	char const *cursor = input;
	int64_t balanced = 0;

	while (*cursor) {
		if (*cursor == begin)
			++balanced;
		else if (*cursor == end)
			--balanced;
		++cursor;
	}

	if (balanced < 0) return PloyError("read_delimiters: missing begin");
	if (balanced > 0) return PloyError("read_delimiters: missing end");

	return PloyNil;
}

Ploy *
read_form(size_t *index, char const **const input)
{
	if (!index) return PloyError("read_form: index is NULL");
	if (!input) return PloyError("read_form: input is NULL");

	char const *cursor = *input;
	size_t length = *index;
	Ploy *objects = PloyNil;

	while (*cursor) {
		Ploy *object = PloyNil;

		switch (*cursor) { // clang-format off
		// Whitespace
		case ' ': case '\n': case '\r': case '\t': case '\v':
			++cursor; ++length; continue;
		// Comment
		case ';': case '#':
			while (*cursor && *++cursor != '\n') { ++length; } continue;
		// List
		case ')': object = PloyNil; break;
		case '(': object = read_list(&length, &cursor); break;
		// Number
		case '-': case '+':
			if (isdigit(cursor[1]))
				object = read_number(&length, &cursor);
			else
				object = read_symbol(&length, &cursor);
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			object = read_number(&length, &cursor); break;
		// String
		case '\"': object = read_string(&length, &cursor); break;
		// Symbol
		default: object = read_symbol(&length, &cursor);
		} // clang-format on

		if (!object) return PloyError("read_form: object is NULL");
		if (object->type == PloyERROR) return object;
		objects = PloyCons(object, objects);
		if (object->type == PloyNIL) break;
	}

	*input = cursor;

	return objects;
}

Ploy *
read_list(size_t *index, char const **const input)
{
	if (!index) return PloyError("read_list: index is NULL");
	if (!input) return PloyError("read_list: input is NULL");

	char const *cursor = *input;
	size_t length = 0;

	if (*cursor != '(') return PloyError("read_list: missing open parenthesis `(`");
	cursor = ++*input;
	length = *index;

	Ploy *object = read_form(&length, &cursor);
	if (*cursor != ')') return PloyError("read_list: missing close parenthesis `)`");
	*input = ++cursor;

	return object;
}

Ploy *
read_number(size_t *index, char const **const input)
{
	if (!index) return PloyError("read_number: index is NULL");
	if (!input) return PloyError("read_number: input is NULL");

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

	char *const number = malloc(length + 1);
	memcpy(number, *input, length);
	number[length] = '\0';

	Ploy *obj = PloyNumber(strtoll(number, NULL, 10));
	free(number);

	*input = cursor;
	*index += length;
	return obj;
}

Ploy *
read_string(size_t *index, char const **const input)
{
	if (!index) return PloyError("read_string: index is NULL");
	if (!input) return PloyError("read_string: input is NULL");

	char const *cursor = *input;
	size_t length = 0;

	if (*cursor != '\"') return PloyError("read_string: Missing open '\"'");
	cursor = ++*input;
	*index += 1;

	while (*cursor && *cursor != '\"') {
		++cursor;
		++length;
	}

	if (*cursor != '\"') return PloyError("read_string: Missing close '\"'");
	++cursor;

	char *const string = GC_MALLOC(length + 1);
	memcpy(string, *input, length);
	string[length] = '\0';

	*input = cursor;
	*index += ++length;
	return PloyString(string);
}

Ploy *
read_symbol(size_t *index, char const **const input)
{
	if (!index) return PloyError("read_symbol: index is NULL");
	if (!input) return PloyError("read_symbol: input is NULL");

	char const *cursor = *input;
	size_t length = 0;

	while (*cursor && !strchr(TOKENS, *cursor)) {
		++cursor;
		++length;
	}
	if (length == 0) return PloyError("read_symbol: invalid length 0");

	char *symbol = GC_MALLOC(length + 1);
	memcpy(symbol, *input, length);
	symbol[length] = '\0';

	*input = cursor;
	*index += length;

	// TODO: jcmdln: Use 'Define'
	Ploy *new = GC_MALLOC(sizeof(*new));
	new->type = PloySYMBOL;
	new->symbol = symbol;
	return new;
}
