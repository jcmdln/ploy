// SPDX-License-Identifier: ISC

#pragma once

#include <cstdint>

#include <string>
#include <string_view>

extern "C" {
#include <gc.h>
}

class Object {
public:
	Object(){};
	virtual ~Object() = default;

	enum class Type {
		Nil = 0,
		Boolean,
		Error,
		Keyword,
		Lambda,
		List,
		Number,
		String,
		Symbol,
	};
	virtual Type type() const = 0;
};

class Boolean : public Object {
public:
	Boolean(bool value) : value{ value } {};
	virtual ~Boolean() = default;

	bool value;
	Type type() const override
	{
		return Type::Boolean;
	}
};

class Error : public Object {
public:
	Error(char *value) : value{ value } {};
	virtual ~Error() = default;

	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
	Type type() const override
	{
		return Type::Error;
	}
};

class Keyword : public Object {
public:
	Keyword(char *value) : value{ value } {};
	virtual ~Keyword() = default;

	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
	Type type() const override
	{
		return Type::Keyword;
	}
};

class Lambda : public Object {
public:
	Lambda(Object *env, Object *args, Object *body)
	    : env{ env }, args{ args }, body{ body } {};
	virtual ~Lambda() = default;

	Object *env{ (Object *)GC_MALLOC(sizeof(*env)) };
	Object *args{ (Object *)GC_MALLOC(sizeof(*args)) };
	Object *body{ (Object *)GC_MALLOC(sizeof(*body)) };
	Type type() const override
	{
		return Type::Lambda;
	}
};

class List : public Object {
public:
	List(Object *car, Object *cdr) : car{ car }, cdr{ cdr } {};
	virtual ~List() = default;

	Object *car{ (Object *)GC_MALLOC(sizeof(*car)) };
	Object *cdr{ (Object *)GC_MALLOC(sizeof(*cdr)) };
	Type type() const override
	{
		return Type::List;
	}
};

class Number : public Object {
public:
	Number(std::int32_t value) : value{ value } {};
	virtual ~Number() = default;

	std::int32_t value;
	Type type() const override
	{
		return Type::Number;
	}
};

class String : public Object {
public:
	String(char *value) : value{ value } {};
	virtual ~String() = default;

	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
	Type type() const override
	{
		return Type::String;
	}
};

class Symbol : public Object {
public:
	char *value{ (char *)GC_MALLOC(sizeof(*value)) };

	Symbol(char *value) : value{ value } {};
	virtual ~Symbol() = default;
	Type type() const override
	{
		return Type::Symbol;
	}
};

char *object_typename(Object::Type);
