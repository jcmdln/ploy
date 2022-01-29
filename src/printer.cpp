// SPDX-License-Identifier: ISC

#include <iostream>

#include "printer.hpp"

void
printer(Object *obj)
{
	switch (obj->type()) {
	case Object::Type::Nil:
		std::cout << "wnil";
		break;

	case Object::Type::Boolean:
		std::cout << (((Boolean *)obj)->value ? "true" : "false");
		break;

	case Object::Type::Error:
		std::cout << ((Error *)obj)->value;
		break;

	case Object::Type::Keyword:
		std::cout << ":" << ((Keyword *)obj)->value;
		break;

	case Object::Type::Lambda:
		std::cout << "<lambda>";
		break;

	case Object::Type::List:
		obj = print_list((List *)obj);
		break;

	case Object::Type::Number:
		std::cout << ((Number *)obj)->value;
		break;

	case Object::Type::String:
		std::cout << '"' << ((String *)obj)->value << '"';
		break;

	case Object::Type::Symbol:
		std::cout << (((Symbol *)obj)->value);
		break;

	default:
		std::cerr << "error: printer: unknown type'"
			  << object_typename(obj->type()) << "'\n";
		break;
	}
}

Object *
print_list(Object *obj)
{
	std::cout << '(';

	while (obj && obj->type() != Object::Type::Nil) {
		if (obj->type() == Object::Type::List) {
			if (!(((List *)obj)->car)) {
				std::cerr << "error: car is NULL\n";
				exit(1);
			}

			printer(((List *)obj)->car);
			if (obj->type() != Object::Type::List) {
				std::cout << " . ";
				printer(obj);
				break;
			}
		}

		Object *cdr = ((List *)obj)->cdr;
		if (cdr && ((List *)cdr)->type() != Object::Type::Nil) {
			std::cout << ' ';
		}

		obj = cdr;
	}

	std::cout << ')';

	return obj;
}
