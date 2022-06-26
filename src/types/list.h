// SPDX-License-Identifier: ISC

#ifndef PLOY_TYPES_LIST_H
#pragma once

#include <stdint.h>

#include "object.h"

struct list {
	struct object *car;
	struct object *cdr;
};

struct list *list_append(struct list *, struct object *);
struct list *list_copy(const struct list *);
// struct list *list_insert(struct list *, struct object *);
// struct list *list_join(struct list *, struct list *);
int64_t list_length(const struct list *);
struct list *list_new(struct object *, struct object *);
// struct list *list_pop(struct list *, struct object *);
// struct list *list_reverse(struct list *);
// struct list *list_slice(struct list *, int64_t, int64_t);
// struct list *list_sort(struct list *);

#endif // PLOY_TYPES_LIST_H
