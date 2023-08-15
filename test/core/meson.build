# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

car = files('car.c')
cdr = files('cdr.c')
cons = files('cons.c')
read = files('read.c')
reverse = files('reverse.c')

ploy_test += [] + car + cdr + cons + read + reverse

test('core_car', executable('car',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, car]
))

test('core_cdr', executable('cdr',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, cdr]
))

test('core_cons', executable('cons',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, cons]
))

test('core_read', executable('read',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, read]
))

test('core_reverse', executable('reverse',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: ploy_include_dirs,
  sources: [ploy_src, reverse]
))
