// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <assert.h>
#include <stdlib.h>

#include <ploy/builtins.h>
#include <ploy/printer.h>

int
main(void)
{
	const char *expected = "(wew :lad \"Hello, world!\" (wew :lad \"Hello, again!\"))";

	struct object *head = object_nil();
	head = Append(head, object_symbol("wew"));
	head = Append(head, object_keyword("lad"));
	head = Append(head, object_string("Hello, world!"));
	struct object *mid = object_nil();
	mid = Append(mid, object_symbol("foo"));
	mid = Append(mid, object_keyword("bar"));
	mid = Append(mid, object_string("Hello, again!"));
	struct object *tail = object_nil();
	tail = Append(tail, object_symbol("wew"));
	tail = Append(tail, object_keyword("lad"));
	tail = Append(tail, object_string("And yet again!"));

	Print(Append(head, Append(mid, tail)));

	return EXIT_SUCCESS;
}
