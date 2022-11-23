// SPDX-License-Identifier: ISC
//
// Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

#include <stdio.h>

#include <ploy/gc.h>
#include <ploy/type/lambda.h>

struct lambda *
lambda_new(struct object *env, struct object *args, struct object *body)
{
	struct lambda *lambda = (struct lambda *)gc_alloc(sizeof(*lambda));
	lambda->env = env;
	lambda->args = args;
	lambda->body = body;
	return lambda;
}
