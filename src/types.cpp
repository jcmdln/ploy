// SPDX-License-Identifier: ISC

#include "types.hpp"

char *
object_typename(Object::Type type)
{
	switch (type) {
	case Object::Type::Nil:
		return "nil";
	case Object::Type::Boolean:
		return "boolean";
	case Object::Type::Error:
		return "error";
	case Object::Type::Keyword:
		return "keyword";
	case Object::Type::Lambda:
		return "lambda";
	case Object::Type::List:
		return "list";
	case Object::Type::Number:
		return "number";
	case Object::Type::String:
		return "string";
	case Object::Type::Symbol:
		return "symbol";
	}

	return "unknown";
}
