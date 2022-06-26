// SPDX-License-Identifier: ISC

#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <gc.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "builtins.h"
#include "printer.h"
#include "reader.h"
#include "types.h"

void
usage()
{
	printf("usage: ploy [-h]\n\n%s", "-h      Show help output\n");
}

int
main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, ":e")) != -1) {
		switch (opt) {
		default:
			usage();
			return EXIT_FAILURE;
		}
	}

	puts("ploy v0.0.0\n");

	while (true) {
		char *input = readline("λ ");
		if (!input) {
			return EXIT_FAILURE;
		}

		add_history(input);

		struct object *obj = reader(&input);
		if (obj && obj->type == list_t) {
			printer(fn_car(obj));
		}

		putchar('\n');
	}

	return EXIT_SUCCESS;
}
