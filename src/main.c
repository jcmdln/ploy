// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <gc/gc.h>
#include <readline/history.h>
#include <readline/readline.h>

#include <ploy/ploy.h>

int
repl(void)
{
	puts("ploy v0.0.0\n");

	while (true) {
		char *input = readline("λ ");
		if (!input) {
			fputs("error: main: input is NULL\n", stderr);
			return EXIT_FAILURE;
		}

		add_history(input);
		Print(Eval(Read(input)));
	}

	return EXIT_SUCCESS;
}

int
usage(int exit_code)
{
	const char *using = "usage: ploy [-h] [-e EXPR]\n\n"
						"    -e      Evaluate an expression\n"
						"    -h      Show help output\n";
	printf("%s\n", using);
	return exit_code;
}

int
main(int argc, char **argv)
{
	int opt = 0;
	bool opt_help = false;
	bool opt_exec = false;

	while ((opt = getopt(argc, argv, ":he:")) != -1) {
		switch (opt) {
		case 'e':
			opt_exec = true;
			break;
		case 'h':
			opt_help = true;
			break;
		default:
			return usage(EXIT_FAILURE);
		}
	}

	if (opt_help) return usage(EXIT_SUCCESS);

	if (opt_exec) {
		Print(Eval(Read(argv[2])));
	} else {
		return repl();
	}

	return EXIT_SUCCESS;
}
