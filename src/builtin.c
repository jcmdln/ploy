// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <gc/gc.h>

#include <ploy/type.h>

struct object *printer(struct object *object);
struct object *reader(const char *input);

struct object *
Append(struct object *list, struct object *object) {
	if (!object) {
		return Error("Append: object is NULL");
	}
	if (!list) {
		return Cons(object, Nil());
	}

	struct object *head = list;
	while (head && Car(head) && Cdr(head) && Cdr(head)->type == OBJECT_LIST) {
		head = Cdr(head);
	}
	head->list->cdr = List(object, Nil());

	return list;
}

struct object *
Car(struct object *object) {
	if (!object) {
		return Error("Cdr: object is NULL");
	}
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->car;
}

struct object *
Boolean(bool boolean) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_BOOLEAN;
	object->boolean = boolean;
	return object;
}

struct object *
Cdr(struct object *object) {
	if (!object) {
		return Error("Cdr: object is NULL");
	}
	if (object->type != OBJECT_LIST) {
		return Error("Cdr: object is not of type LIST");
	}
	return object->list->cdr;
}

struct object *
Cons(struct object *car, struct object *cdr) {
	return List(car, cdr);
}

struct object *
Error(const char *error) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_ERROR;
	object->error = error;
	return object;
}

struct object *
Eval(struct object *object) {
	return object;
}

struct object *
Keyword(const char *keyword) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_KEYWORD;
	object->keyword = keyword;
	return object;
}

struct object *
Lambda(struct object *env, struct object *args, struct object *body) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LAMBDA;
	object->lambda = GC_MALLOC(sizeof(*object->lambda));
	object->lambda->env = env;
	object->lambda->args = args;
	object->lambda->body = body;
	return object;
}

struct object *
List(struct object *car, struct object *cdr) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_LIST;
	object->list = GC_MALLOC(sizeof(*object->list));
	object->list->car = car;
	object->list->cdr = cdr;
	return object;
}

struct object *
Nil(void) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NIL;
	return object;
}

struct object *
Number(int64_t number) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_NUMBER;
	object->number = number;
	return object;
}

struct object *
Print(struct object *object) {
	struct object *head = object;
	if (head) {
		printer(head);
		putchar('\n');
	}
	return object;
}

struct object *
Read(const char *input) {
	return reader(input);
}

struct object *
Reverse(struct object *object) {
	if (!object) {
		return Error("Reverse: object is NULL");
	}

	struct object *head = object;
	struct object *reversed = List(NULL, NULL);
	while (head && head->type == OBJECT_LIST && head->list->car) {
		reversed = List(reversed, head->list->car);
		if (!head->list->cdr) {
			break;
		}
		head = head->list->cdr;
	}

	return reversed;
}

struct object *
String(const char *string) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_STRING;
	object->string = string;
	return object;
}

struct object *
Symbol(const char *symbol) {
	struct object *object = GC_MALLOC(sizeof(*object));
	object->type = OBJECT_SYMBOL;
	object->symbol = symbol;
	return object;
}
