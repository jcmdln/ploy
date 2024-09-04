#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <ploy.h>

#ifndef PLOY_VERSION
#define PLOY_VERSION "undefined"
#endif

int rep(char *input);
int repf(char *path);
int repl(void);
int usage(int exit_code);
int version(void);

int
main(int argc, char **argv)
{
	int opt = 0;
	bool opt_exec = false;

	while ((opt = getopt(argc, argv, "hve:")) != -1) {
		switch (opt) {
		case 'h':
			return usage(EXIT_SUCCESS);
		case 'v':
			return version();
		case 'e':
			opt_exec = true;
			break;
		default:
			return usage(EXIT_FAILURE);
		}
	}

	if (opt_exec) {
		puts("error: -e and -f are mutually exclusive");
		return usage(EXIT_FAILURE);
	}

	if (opt_exec) {
		rep(argv[2]);
		putchar('\n');
	} else {
		if (argv[1]) return repf(argv[1]);
		return repl();
	}

	return EXIT_SUCCESS;
}

int
rep(char *input)
{
	PloyPrint(PloyEval(PloyRead(input)));
	return EXIT_SUCCESS;
}

int
repf(char *path)
{
	if (!path) {
		puts("error: repf: path is NULL");
		return EXIT_FAILURE;
	}

	FILE *file = fopen(path, "r");
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
		rep(buffer);
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
		char *input = readline("λ ");
		if (!input || strcmp(input, "") == 0) continue;
		add_history(input);
		rep(input);
		putchar('\n');
		free(input);
	}

	return EXIT_SUCCESS;
}

int
usage(int exit_code)
{
	printf("usage: ploy [-h] [-v] [-e EXPR] [FILE]\n\n"
		   "  -h         Show help output\n"
		   "  -v         Show version\n"
		   "  -e EXPR    Evaluate an expression\n");
	return exit_code;
}

int
version(void)
{
	printf("ploy version %s\n", PLOY_VERSION);
	return EXIT_SUCCESS;
}
