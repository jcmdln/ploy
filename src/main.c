// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <gc/gc.h>
#include <readline/history.h>
#include <readline/readline.h>

#include <ploy/core.h>
#include <ploy/type.h>

int repf(char *path);
int repl(void);

int
usage(int exit_code)
{
	char const *using = "usage: ploy [-h] [-e EXPR | -f FILE]\n\n"
						"    -e      Evaluate an expression\n"
						"    -f      Evaluate contents of a FILE\n"
						"    -h      Show help output\n";
	printf("%s\n", using);
	return exit_code;
}

int
main(int argc, char **argv)
{
	int opt = 0;
	bool opt_exec = false;
	bool opt_file = false;
	bool opt_help = false;

	while ((opt = getopt(argc, argv, "e:f:h")) != -1) {
		switch (opt) {
		case 'e':
			opt_exec = true;
			break;
		case 'f':
			opt_file = true;
			break;
		case 'h':
			opt_help = true;
			break;
		default:
			return usage(EXIT_FAILURE);
		}
	}

	if (opt_help) {
		return usage(EXIT_SUCCESS);
	}

	if (opt_exec && opt_file) {
		puts("error: -e and -f are mutually exclusive");
		return usage(EXIT_FAILURE);
	}

	if (opt_exec) {
		Print(Eval(Read(argv[2])));
	} else if (opt_file) {
		return repf(argv[2]);
	} else {
		return repl();
	}

	return EXIT_SUCCESS;
}

int
repf(char *path)
{
	FILE *file = fopen(path, "r");
	if (!file) {
		printf("error: failed to fopen '%s'\n", path);
		return EXIT_FAILURE;
	}

	char *buffer = NULL;
	size_t buffer_length = 0;
	if (getdelim(&buffer, &buffer_length, EOF, file) == -1) {
		printf("error: failed to read FILE\n");
		if (buffer) {
			free(buffer);
		}
		return EXIT_FAILURE;
	}

	Print(Eval(Read(buffer)));
	free(buffer);
	return EXIT_SUCCESS;
}

int
repl(void)
{
	puts("ploy v0.0.0\n");

	while (true) {
		char *input = readline("λ ");
		if (!input || strlen(input) < 1) {
			continue;
		}

		add_history(input);
		Print(Eval(Read(input)));
	}

	return EXIT_SUCCESS;
}
