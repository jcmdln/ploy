// SPDX-License-Identifier: ISC

#include <stdint.h>
#include <stdlib.h>

#include <gc.h>

#include "list.h"

struct list *
list_append(struct list *list, struct object *obj)
{
	if (!list) {
		return NULL;
	}

	struct list *list_p = list;

	if (!list_p->car || list_p->car->type == nil_t) {
		list_p->car = obj;
		return list;
	}

	while (list_p && list_p->cdr && list_p->cdr->type == list_t) {
		list_p = list_p->cdr->list;
	}

	list_p->cdr = object_new_list(list_new(obj, NULL));

	return list;
}

struct list *
list_copy(const struct list *list)
{
	struct list *copy = list_new(list->car, list->cdr);
	return copy;
}

// FIXME: implement this
struct list *
list_insert(struct list *list, struct object *obj)
{
	return list;
}

// FIXME: implement this
struct list *
list_join(struct list *dest, struct list *src)
{
	struct list *list = NULL;

	return list;
}

int64_t
list_length(const struct list *list)
{
	int64_t items = 0;

	while (list && list->car && list->car->type != nil_t) {
		++items;

		if (!list->cdr || list->cdr->type == nil_t) {
			break;
		}

		if (list->cdr->type != list_t) {
			++items;
			break;
		}

		list = list->cdr->list;
	}

	return items;
}

struct list *
list_new(struct object *car, struct object *cdr)
{
	struct list *list = (struct list *)GC_MALLOC(sizeof(*list));

	list->car = car;

	if (cdr && cdr->type != nil_t) {
		struct list *cdr_list = (struct list *)GC_MALLOC(sizeof(*list));
		cdr_list->car = cdr;
		cdr_list->cdr = NULL;
		list->cdr = object_new_list(cdr_list);
	} else {
		list->cdr = cdr;
	}

	return list;
}

// FIXME: implement this
struct list *
list_remove(struct list *dest, struct object *obj)
{
	return dest;
}

// FIXME: implement this
struct list *
list_reverse(struct list *list)
{
	return list;
}

// FIXME: implement this
struct list *
list_slice(struct list *list, int64_t offset, int64_t length)
{
	return list;
}

// FIXME: implement this
struct list *
list_sort(struct list *list)
{
	return list;
}
