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

	Type type() const override { return Type::Boolean; }
	bool value;
};

class Error : public Object {
public:
	Error(char *value) : value{ value } {};
	virtual ~Error() = default;

	Type type() const override { return Type::Error; }
	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
};

class Keyword : public Object {
public:
	Keyword(char *value) : value{ value } {};
	virtual ~Keyword() = default;

	Type type() const override { return Type::Keyword; }
	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
};

class Lambda : public Object {
public:
	Lambda(Object *env = nullptr, Object *args = nullptr,
	    Object *body = nullptr)
	    : env{ env }, args{ args }, body{ body } {};
	virtual ~Lambda() = default;

	Type type() const override { return Type::Lambda; }
	Object *env{ (Object *)GC_MALLOC(sizeof(*env)) };
	Object *args{ (Object *)GC_MALLOC(sizeof(*args)) };
	Object *body{ (Object *)GC_MALLOC(sizeof(*body)) };
};

class List : public Object {
public:
	List(Object *car = nullptr, Object *cdr = nullptr)
	    : car{ car }, cdr{ cdr } {};
	virtual ~List() = default;

	Type type() const override { return Type::List; }
	Object *car{ (Object *)GC_MALLOC(sizeof(*car)) };
	Object *cdr{ (Object *)GC_MALLOC(sizeof(*cdr)) };
};

class Number : public Object {
public:
	Number(std::int32_t value) : value{ value } {};
	virtual ~Number() = default;

	Type type() const override { return Type::Number; }
	std::int32_t value;
};

class String : public Object {
public:
	String(char *value) : value{ value } {};
	virtual ~String() = default;

	Type type() const override { return Type::String; }
	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
};

class Symbol : public Object {
public:
	Symbol(char *value) : value{ value } {};
	virtual ~Symbol() = default;

	Type type() const override { return Type::Symbol; }
	char *value{ (char *)GC_MALLOC(sizeof(*value)) };
};

char *object_typename(Object::Type);
