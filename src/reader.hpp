// SPDX-License-Identifier: ISC

#include <cstdint>

#include <string>
#include <string_view>

extern "C" {
#include <gc.h>
}

#include "types.hpp"

Object *reader(char **);

Object *read_keyword(char **);
Object *read_list(char **);
Object *read_number(char **);
Object *read_quote(char **);
Object *read_string(char **);
Object *read_symbol(char **);
