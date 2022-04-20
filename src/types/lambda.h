// SPDX-License-Identifier: ISC

#ifndef TYPES_LAMBDA_H
#pragma once

struct lambda {
	struct object *env;
	struct object *args;
	struct object *body;
};

#endif // TYPES_LAMBDA_H
