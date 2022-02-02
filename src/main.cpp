// SPDX-License-Identifier: ISC

extern "C" {
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <readline/history.h>
#include <readline/readline.h>
}

#include "builtins.hpp"
#include "printer.hpp"
#include "reader.hpp"
#include "types.hpp"

void
usage()
{
	printf("usage: ploy [-h]\n\n%s", "-h      Show help output\n");
}

int
main(int argc, char **argv)
{
	auto opt{ 0 };

	while ((opt = getopt(argc, argv, ":e")) != -1) {
		switch (opt) {
		default:
			usage();
			return EXIT_FAILURE;
		}
	}

	puts("ploy v0.0.0\n");

	while (true) {
		char *input{ readline("λ ") };
		if (!input) {
			return EXIT_FAILURE;
		}

		add_history(input);

		auto *obj{ reader(&input) };
		if (obj) {
			printer(fn_car(obj));
		}

		putchar('\n');
	}

	return EXIT_SUCCESS;
}
