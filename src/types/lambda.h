// SPDX-License-Identifier: ISC

#ifndef PLOY_TYPES_LAMBDA_H
#pragma once

struct lambda {
	struct object *env;
	struct object *args;
	struct object *body;
};

#endif // PLOY_TYPES_LAMBDA_H
