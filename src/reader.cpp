// SPDX-License-Identifier: ISC

extern "C" {
#include <string.h>
}

#include "reader.hpp"

Object *
reader(char **input)
{
	auto *cursor{ *input };
	Object *obj{ nullptr };

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
			obj = new List(read_keyword(&cursor), obj);
			break;

		// list
		case '(':
			obj = new List(read_list(&cursor), obj);
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
			obj = new List(read_number(&cursor), obj);
			break;

		// quote
		case '\'':
		// quasiquote
		case '`':
			++cursor;
			obj = new List(read_quote(&cursor), obj);
			break;

		// string
		case '"':
			++cursor;
			obj = new List(read_string(&cursor), obj);
			break;

		// symbol
		default:
			obj = new List(read_symbol(&cursor), obj);
			break;
		}
	};

	*input = cursor;

	return obj;
}

Object *
read_keyword(char **input)
{
	auto *cursor{ *input };
	auto position{ 0 };

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

	Object *obj{ new Keyword(strndup(*input, position)) };
	*input = cursor;

	return obj;
}

Object *
read_list(char **input)
{
	auto *cursor{ *input };
	Object *obj{ nullptr };

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

Object *
read_number(char **input)
{
	auto *cursor{ *input };
	auto position{ 0 };

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

	Object *obj{ new Number(atoi(strndup(*input, position))) };
	*input = cursor;

	return obj;
}

Object *
read_quote(char **input)
{
	auto *cursor{ *input };
	auto position{ 0 };

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

	Object *obj{ new Symbol(strndup(*input, position)) };
	*input = cursor;

	return obj;
}

Object *
read_string(char **input)
{
	auto *cursor{ *input };
	auto position{ 0 };

	while (*cursor && *cursor != '\"') {
		++cursor;
		++position;
	}

	if (*cursor != '\"') {
		fputs("error: reader: no matching '\"'", stderr);
		exit(1);
	}

	Object *obj{ new String(strndup(*input, position)) };
	*input = ++cursor;

	return obj;
}

Object *
read_symbol(char **input)
{
	auto *cursor{ *input };
	auto position{ 0 };

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

	Object *obj{ new Symbol(strndup(*input, position)) };
	*input = cursor;

	return obj;
}
