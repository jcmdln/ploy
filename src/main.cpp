// SPDX-License-Identifier: ISC

#include <cstdlib>
#include <iostream>

extern "C" {
#include <gc.h>
#include <getopt.h>

#include <readline/history.h>
#include <readline/readline.h>
}

#include "ploy.hpp"

int
main(int argc, char **argv)
{
	auto opt = 0;

	while ((opt = getopt(argc, argv, ":e")) != -1) {
		switch (opt) {
		default:
			std::cerr << "usage: ploy [-h]\n";
			return EXIT_FAILURE;
		}
	}

	std::cout << "ploy v0.0.0\n";
	std::cout << "press ctrl+c to exit\n";

	while (true) {
		auto *input = readline("λ ");
		if (!input) {
			return EXIT_FAILURE;
		}
		add_history(input);

		auto *obj = reader(&input);
		if (obj) {
			printer(fn_car(obj));
		}
		std::cout << '\n';
	}

	return EXIT_SUCCESS;
}

Object *
env_get(Object *env, Object *symbol, Object *result)
{
	auto *bs = fn_car(env);
	auto *parent = fn_cdr(env);

	while (bs->type != Object::Type::Nil) {
		Object *b = bs->list->car;
		if (fn_car(b)->symbol == symbol->symbol) {
			result = fn_cdr(b);
			return &Nil;
		}

		bs = fn_cdr(bs);
	}

	if (parent->type == Object::Type::Nil) {
		std::cerr << "error: unbound symbol";
		exit(1);
	}

	return env_get(parent, symbol, result);
}

void
env_set(Object **env, char *symbol, Object *value)
{
	auto *env_p = *env;

	while (env_p->type != Object::Type::Nil) {
		auto *p = fn_car(env_p);
		if (p->type == Object::Type::Symbol && p->symbol == symbol) {
			p->list->cdr = value;
			return;
		}
		env_p = fn_cdr(env_p);
	}

	auto *car = object_new_list(object_new_symbol(symbol), value);
	env_p = object_new_list(car, env_p);
}

Object *
fn_add(Object *obj)
{
	auto sum = 0;

	while (obj && obj->type != Object::Type::Nil) {
		if (obj->type != Object::Type::Number) {
			std::cerr << "error: '+': invalid argument(s)\n";
		}

		sum += obj->number;
		obj = obj->list->cdr;
	}

	return object_new_number(sum);
}

Object *
fn_car(Object *obj)
{
	return obj->list->car;
}

Object *
fn_cdr(Object *obj)
{
	return obj->list->cdr;
}

Object *
fn_cons(Object *obj)
{
	return object_new_list(fn_car(obj), fn_car(fn_cdr(obj)));
}

Object *
fn_eval(Object *obj)
{
	return obj;
}

void
fn_print(Object *obj)
{
	printer(obj);
}

Object *
fn_typeof(Object *obj)
{
	return object_new_string(object_typename(obj->type));
}

Object *
object_new(Object::Type type)
{
	Object *obj = (Object *)GC_MALLOC(sizeof(*obj));

	obj->type = type;

	return obj;
}

Object *
object_new_keyword(char *value)
{
	auto *obj = object_new(Object::Type::Keyword);

	obj->keyword = value;

	return obj;
}

Object *
object_new_lambda(Object *env, Object *args, Object *body)
{
	auto *obj = object_new(Object::Type::Lambda);

	obj->lambda = (struct Lambda *)GC_MALLOC(sizeof(*obj->lambda) * 3);
	obj->lambda->env = env;
	obj->lambda->args = args;
	obj->lambda->body = body;

	return obj;
}

Object *
object_new_list(Object *car, Object *cdr)
{
	auto *obj = object_new(Object::Type::List);

	obj->list = (struct List *)GC_MALLOC(sizeof(*obj->list) * 2);
	obj->list->car = car;
	obj->list->cdr = cdr;

	return obj;
}

Object *
object_new_number(std::int32_t number)
{
	auto *obj = object_new(Object::Type::Number);

	obj->number = number;

	return obj;
}

Object *
object_new_string(char *value)
{
	auto *obj = object_new(Object::Type::String);

	obj->string = value;

	return obj;
}

Object *
object_new_symbol(char *value)
{
	auto *obj = object_new(Object::Type::Symbol);

	obj->symbol = value;

	return obj;
}

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
	default:
		return NULL;
	}
}

void
printer(Object *obj)
{
	char *type_name = nullptr;

	if (!obj) {
		obj = &Nil;
	}

	switch (obj->type) {
	case Object::Type::Nil:
		std::cout << "nil";
		break;

	case Object::Type::Boolean:
		std::cout << (obj->boolean ? "true" : "false");
		break;

	case Object::Type::Error:
		std::cout << obj->error;
		break;

	case Object::Type::Keyword:
		std::cout << ":" << obj->keyword;
		break;

	case Object::Type::Lambda:
		std::cout << "<lambda>";
		break;

	case Object::Type::List:
		std::cout << '(';

		while (obj && obj->type != Object::Type::Nil) {
			if (!(obj->list->car)) {
				std::cerr << "error: car is NULL\n";
				exit(1);
			}

			printer(obj->list->car);
			if (obj->type != Object::Type::List) {
				std::cout << " . ";
				printer(obj);
				break;
			}

			Object *cdr = obj->list->cdr;
			if (cdr && cdr->type != Object::Type::Nil) {
				std::cout << ' ';
			}
			obj = cdr;
		}

		std::cout << ')';
		break;

	case Object::Type::Number:
		std::cout << obj->number;
		break;

	case Object::Type::String:
		std::cout << '"' << obj->string << '"';
		break;

	case Object::Type::Symbol:
		std::cout << obj->symbol;
		break;

	default:
		if ((type_name = object_typename(obj->type))) {
			std::cerr << "error: unknown type'" << type_name
				  << "'\n";
		} else {
			std::cerr << "error: type is mangled \n";
		}
		break;
	}
}

Object *
reader(char **input)
{
	auto *cursor = *input;
	Object *obj = nullptr;

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

		// case '+':
		// case '-':
		//	if (isdigit(cur[1])) {
		//		cur = read_number(&cur);
		//		break;
		//	}
		//	break;
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

		case '\'':
		case '`':
			++cursor;
			obj = object_new_list(read_quote(&cursor), obj);
			break;

		case '"':
			++cursor;
			obj = object_new_list(read_string(&cursor), obj);
			break;

		default:
			obj = object_new_list(read_symbol(&cursor), obj);
			break;
		}
	};

	*input = cursor;

	return obj;
}

Object *
read_keyword(char **input)
{
	auto *cursor = *input;
	auto position = 0;

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

	auto *obj = object_new_keyword(strndup(*input, position));
	*input = cursor;

	return obj;
}

Object *
read_list(char **input)
{
	auto *cursor = *input;
	Object *obj = nullptr;

	while (*cursor) {
		switch (*cursor) {
		case '\0':
			std::cerr << "error: read_list: "
				  << "unexpected end of input stream";
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
	auto *cursor = *input;
	auto position = 0;

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

	auto *obj = object_new_number(atoi(strndup(*input, position)));
	*input = cursor;

	return obj;
}

Object *
read_quote(char **input)
{
	auto *cursor = *input;
	auto position = 0;

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

	auto *obj = object_new_symbol(strndup(*input, position));
	*input = cursor;

	return obj;
}

Object *
read_string(char **input)
{
	auto *cursor = *input;
	auto position = 0;

	if (!strchr(cursor, '\"')) {
		std::cerr << "reader: string: "
			  << "no matching delimiter '\"'";
		exit(1);
	}

	while (*cursor && *cursor != '\"') {
		++cursor;
		++position;
	}

	auto *obj = object_new_string(strndup(*input, position));
	*input = ++cursor;

	return obj;
}

Object *
read_symbol(char **input)
{
	auto *cursor = *input;
	auto position = 0;

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

	auto *obj = object_new_symbol(strndup(*input, position));
	*input = cursor;

	return obj;
}

void
runtime_init(void)
{
	// FIXME: symbols are not being added to env correctly
	Object *env = object_new_list(&Nil, &Nil);

	env_set(&env, "nil", &Nil);
	env_set(&env, "true", &True);
	env_set(&env, "false", &False);

	// env_set_fn(env, "+", fn_add);
	// env_set_fn(env, "-", fn_subtract);
	// env_set_fn(env, "*", fn_multiply);
	// env_set_fn(env, "/", fn_divide);
	// env_set_fn(env, "%", fn_modulo);
	// env_set_fn(env, "^", fn_exponent);
	// env_set_fn(env, "=", fn_equal);
	// env_set_fn(env, ">", fn_greater_than);
	// env_set_fn(env, ">=", fn_greater_than_or_equal);
	// env_set_fn(env, "<", fn_less_than);
	// env_set_fn(env, "<=", fn_less_than_or_equal);
}
