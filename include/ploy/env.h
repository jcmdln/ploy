// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_ENV_H
#pragma once

#include <ploy/type/object.h>

struct env {
	struct env *parent;
	struct object *objects;
};

#endif // PLOY_ENV_H
