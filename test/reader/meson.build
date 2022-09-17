# SPDX-License-Identifier: ISC
#
# Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

test('test_reader', executable('test_reader',
  dependencies: bdw_gc,
  include_directories: ploy_includes,
  sources: files(test_sources, 'reader.c')
))

subdir('lexer')
subdir('parser')
