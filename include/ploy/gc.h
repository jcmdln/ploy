// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_GC_H
#pragma once

#include <stddef.h>

void *gc_alloc(size_t size);
void gc_free(void *target);

#endif // PLOY_GC_H
