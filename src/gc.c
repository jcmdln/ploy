// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <gc/gc.h>

#include <ploy/ploy.h>

void *
gc_alloc(size_t size)
{
	return GC_MALLOC(size);
}

void
gc_free(void *target)
{
	GC_FREE(target);
}
