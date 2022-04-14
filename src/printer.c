// SPDX-License-Identifier: ISC

#include <stdio.h>
#include <stdlib.h>

#include "printer.h"

void
printer(struct object *obj)
{
	switch (obj->type) {
	case nil_t:
		printf("nil");
		break;

	case boolean_t:
		printf(obj->boolean ? "true" : "false");
		break;

	case error_t:
		printf("%s", obj->error);
		break;

	case keyword_t:
		printf(":%s", obj->keyword);
		break;

	case lambda_t:
		printf("<lambda>");
		break;

	case list_t:
		print_list(obj);
		break;

	case number_t:
		printf("%ld", obj->number);
		break;

	case string_t:
		printf("\"%s\"", obj->string);
		break;

	case symbol_t:
		printf("%s", obj->symbol);
		break;

	default:
		fprintf(stderr, "error: printer: unknown type '%s'", object_typename(obj->type));
		break;
	}
}

void
print_list(struct object *obj)
{
	putchar('(');

	while (obj && obj->type != nil_t) {
		if (obj->type == list_t) {
			if (!(obj->list->car)) {
				fputs("error: car is NULL\n", stderr);
				exit(1);
			}

			printer(obj->list->car);
			if (obj->type != list_t) {
				printf(" . ");
				printer(obj);
				break;
			}
		}

		struct object *cdr = obj->list->cdr;
		if (cdr && cdr->type != nil_t) {
			putchar(' ');
		}

		obj = cdr;
	}

	putchar(')');
}
