// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <ploy/ploy.h>

int
main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
		case 'h':
			printf("usage: ploy [-h]\n\n%s", "-h      Show help output\n");
			return EXIT_SUCCESS;
		default:
			printf("usage: ploy [-h]\n\n%s", "-h      Show help output\n");
			return EXIT_FAILURE;
		}
	}

	puts("ploy v0.0.0\n");

	while (true) {
		char *input = readline("λ ");
		if (!input) {
			fputs("error: main: input is invalid\n", stderr);
			return EXIT_FAILURE;
		}

		add_history(input);

		struct object *objects = Print(Eval(Read(input)));
		if (objects) {
			gc_free(objects);
		}
	}

	return EXIT_SUCCESS;
}
