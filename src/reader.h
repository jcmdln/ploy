// SPDX-License-Identifier: ISC

#ifndef READER_H
#pragma once

#include "types.h"

struct object *reader(char **);

struct object *read_keyword(char **);
struct object *read_list(char **);
struct object *read_number(char **);
struct object *read_quote(char **);
struct object *read_string(char **);
struct object *read_symbol(char **);

#endif // READER_H
