// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include <ploy/gc.h>
#include <ploy/type/list.h>
#include <ploy/type/object.h>

struct list *
list_new(struct object *element, struct object *next)
{
	struct list *list = (struct list *)gc_alloc(sizeof(*list));
	list->element = element;
	list->next = next;
	return list;
}

struct list *
list_append(struct list *list, struct object *element)
{
	if (!element) {
		fputs("error: list_append: element is NULL\n", stderr);
		return NULL;
	}
	if (!list) {
		return list_new(element, object_nil());
	}

	struct list *head = list;
	while (head && head->element && head->next && head->next->type == OBJECT_LIST) {
		head = head->next->list;
	}
	head->next = object_list(list_new(element, object_nil()));

	return list;
}

int64_t
list_length(struct list *list)
{
	int64_t length = 0;
	struct list *head = list;
	while (head && head->element) {
		head = head->next->list;
		++length;
	}
	return length;
}

struct list *
list_pop(struct list *list)
{
	struct list *head = list;
	while (head && head->next && head->next->list) {
		head = head->next->list;
	}
	head->next = object_nil();
	return list;
}

struct list *
list_push(struct list *list, struct object *element)
{
	return list_new(element, object_list(list));
}

struct list *
list_reverse(struct list *list)
{
	struct list *head = list;
	struct list *reversed = list_new(NULL, NULL);
	while (head && head->element) {
		reversed = list_push(reversed, head->element);
		if (!head->next) {
			break;
		}
		head = head->next->list;
	}
	return reversed;
}
