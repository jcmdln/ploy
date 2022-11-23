// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy/builtins.h>
#include <ploy/reader/parser.h>

int
main(void)
{
	puts("form: (wew :lad \"foo bar\")");
	Print(Read("wew :lad \"foo bar\""));
	Print(Read("(wew :lad \"foo bar\")"));
	putchar('\n');

	puts("form: (wew :lad \"foo bar\" (wew :lad \"foo bar\"))");
	Print(Read("wew :lad \"foo bar\" (wew :lad \"foo bar\")"));
	Print(Read("(wew :lad \"foo bar\" (wew :lad \"foo bar\"))"));
	putchar('\n');

	puts("form: (wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))");
	Print(Read("wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\"))"));
	Print(Read("(wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))"));
	putchar('\n');

	puts("form: (((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\")");
	Print(Read("((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\""));
	Print(Read("(((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\")"));
	putchar('\n');

	puts("form: ((wew :lad \"foo bar\") wew :lad \"foo bar\")");
	Print(Read("(wew :lad \"foo bar\") wew :lad \"foo bar\""));
	Print(Read("((wew :lad \"foo bar\") wew :lad \"foo bar\")"));

	return EXIT_SUCCESS;
}
