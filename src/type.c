// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <gc.h>

#include <ploy/type.h>

Object *
Boolean(bool boolean)
{
	Object *const new = GC_MALLOC(sizeof(*new));
	new->type = TYPE_BOOLEAN;
	new->boolean = boolean;
	return new;
}

Object *
Error(char const *const error)
{
	if (!error) return Error("Error: error is NULL");

	Object *const object = GC_MALLOC(sizeof(*object));
	object->type = TYPE_ERROR;
	object->string = error;
	return object;
}

Object *
Number(int64_t number)
{
	Object *const new = GC_MALLOC(sizeof(*new));
	new->type = TYPE_NUMBER;
	new->number = number;
	return new;
}

Object *
String(char const *const string)
{
	if (!string) return Error("String: string is NULL");

	Object *new = GC_MALLOC(sizeof(*new));
	new->type = TYPE_STRING;
	new->string = string;
	return new;
}

Object *
Symbol(char const *const symbol)
{
	if (!symbol) return Error("Symbol: symbol is NULL");

	Object *const new = GC_MALLOC(sizeof(*new));
	new->type = TYPE_SYMBOL;
	new->string = symbol;
	return new;
}
