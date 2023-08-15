# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

add = files('add.c')
divide = files('divide.c')
multiply = files('multiply.c')
subtract = files('subtract.c')

ploy_test += [] + add + divide + multiply + subtract

test('math_add', executable('add',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, add]
))

test('math_divide', executable('divide',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, divide]
))

test('math_multiply', executable('multiply',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, multiply]
))

test('math_subtract', executable('subtract',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, subtract]
))
