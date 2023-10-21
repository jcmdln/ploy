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
#include <ploy/math.h>

#ifndef PLOY_VERSION
#define PLOY_VERSION "undefined"
#endif

int repf(char const *path);
int repl(void);

int
usage(int exit_code)
{
	printf("usage: ploy [-h] [-e EXPR] [-f FILE]\n\n"
		   "  -h         Show help output\n"
		   "  -e EXPR    Evaluate an expression\n"
		   "  -f FILE    Evaluate contents of a FILE\n\n");
	return exit_code;
}

void
version(void)
{
	const char *version = (const char *)PLOY_VERSION;
	printf("ploy version %s\n", version);
}

int
main(int argc, char **argv)
{
	int opt = 0;
	bool opt_exec = false;
	bool opt_file = false;

	while ((opt = getopt(argc, argv, "he:f:")) != -1) {
		switch (opt) {
		case 'h':
			return usage(EXIT_SUCCESS);
		case 'e':
			opt_exec = true;
			break;
		case 'f':
			opt_file = true;
			break;
		default:
			return usage(EXIT_FAILURE);
		}
	}

	if (opt_exec && opt_file) {
		puts("error: -e and -f are mutually exclusive");
		return usage(EXIT_FAILURE);
	}

	if (opt_exec) {
		Print(Eval(Read(argv[2])));
		putchar('\n');
	} else {
		if (opt_file) return repf(argv[2]);
		return repl();
	}

	return EXIT_SUCCESS;
}

int
repf(char const *path)
{
	FILE *const file = fopen(path, "r");
	if (!file) {
		printf("error: failed to fopen '%s'\n", path);
		return EXIT_FAILURE;
	}

	char *buffer = NULL;
	size_t buffer_length = 0;
	int retval = EXIT_SUCCESS;
	if (getdelim(&buffer, &buffer_length, EOF, file) == -1) {
		puts("error: failed to read FILE");
		retval = EXIT_FAILURE;
	} else {
		Print(Eval(Read(buffer)));
		putchar('\n');
	}

	if (buffer) free(buffer);
	(void)fclose(file);

	return retval;
}

int
repl(void)
{
	version();

	while (true) {
		char *const input = readline("λ ");
		if (!input) continue;
		add_history(input);

		Print(Eval(Read(input)));
		free(input);

		putchar('\n');
	}

	return EXIT_SUCCESS;
}
