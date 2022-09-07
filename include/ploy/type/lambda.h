// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_TYPE_LAMDBA_H
#pragma once

#include <ploy/type/object.h>

struct lambda {
	struct object *env;
	struct object *args;
	struct object *body;
};

struct lambda *lambda_new(struct object *env, struct object *args, struct object *body);

#endif // PLOY_TYPE_LAMDBA_H
