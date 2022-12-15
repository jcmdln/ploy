// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_TYPE_LIST_H
#pragma once

#include <stdlib.h>

struct list {
	struct object *element;
	struct object *next;
};

struct list *new_list(struct object *element, struct object *next);

struct list *list_append(struct list *list, struct object *element);
size_t list_length(struct list *list);
struct list *list_pop(struct list *list);
struct list *list_push(struct list *list, struct object *element);
struct list *list_reverse(struct list *list);

#endif // PLOY_TYPE_LIST_H
