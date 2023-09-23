// SPDX-License-Identifier: ISC
//
// Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

#ifndef PLOY_MATH_H
#define PLOY_MATH_H
#pragma once

#include "type.h"

//
// Arithmetic
//

Object const *Add(Object const *object);
Object const *Subtract(Object const *object);
Object const *Multiply(Object const *object);
Object const *Divide(Object const *object);

Object const *Exponent(Object const *object);
Object const *Log(Object const *object);
Object const *Modulo(Object const *object);
Object const *NthRoot(Object const *object);

#endif // PLOY_MATH_H
