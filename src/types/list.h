// SPDX-License-Identifier: ISC

#ifndef TYPES_LIST_H
#pragma once

#include <stdint.h>

#include "object.h"

struct list {
	struct object *car;
	struct object *cdr;

	// TODO: Add `head` and `tail` fields to `struct list` to avoid (some) traversals
	// struct object *head;
	// struct object *tail;
};

struct list *list_append(struct list *, struct object *);
struct list *list_copy(const struct list *);
struct list *list_insert(struct list *, struct object *); // FIXME: implement this
struct list *list_join(struct list *, struct list *);	  // FIXME: implement this
int64_t list_length(const struct list *);
struct list *list_new(struct object *, struct object *);
struct list *list_pop(struct list *, struct object *);	  // FIXME: implement this
struct list *list_reverse(struct list *);		  // FIXME: implement this
struct list *list_slice(struct list *, int64_t, int64_t); // FIXME: implement this
struct list *list_sort(struct list *);			  // FIXME: implement this

#endif // TYPES_LIST_H
