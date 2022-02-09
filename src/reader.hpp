// SPDX-License-Identifier: ISC

#pragma once

#include "types.hpp"

Object *reader(char **);

Object *read_keyword(char **);
Object *read_list(char **);
Object *read_number(char **);
Object *read_quote(char **);
Object *read_string(char **);
Object *read_symbol(char **);
