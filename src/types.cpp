// SPDX-License-Identifier: ISC

extern "C" {
#include <gc.h>
}

#include "types.hpp"

char *
object_typename(Object::Type type)
{
	char *str{ (char *)GC_MALLOC(sizeof(*str)) };

	switch (type) {
	case Object::Type::Nil:
		str = "nil";
		break;
	case Object::Type::Boolean:
		str = "boolean";
		break;
	case Object::Type::Error:
		str = "error";
		break;
	case Object::Type::Keyword:
		str = "keyword";
		break;
	case Object::Type::Lambda:
		str = "lambda";
		break;
	case Object::Type::List:
		str = "list";
		break;
	case Object::Type::Number:
		str = "number";
		break;
	case Object::Type::String:
		str = "string";
		break;
	case Object::Type::Symbol:
		str = "symbol";
		break;
	default:
		str = "unknown";
	}

	return str;
}
