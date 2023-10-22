# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

project('ploy', 'c',
  default_options: [
    'buildtype=release',
    'c_std=c11',
    'warning_level=3',
    'werror=false',
  ],
  license: 'ISC',
  meson_version: '>=0.46',
  version: '0.0.0',
)

#
# Compilation
#

compiler = meson.get_compiler('c', native: true)
add_project_arguments(compiler.get_supported_arguments([
  '-fshort-wchar',
  '-fstrict-aliasing',
  '-funsigned-char',
  '-Werror=cast-qual',
  '-Werror=implicit-int',
  '-Werror=restrict',
  '-Werror=strict-prototypes',
  '-Werror=switch',
  '-Werror=vla',
  '-Werror=write-strings',
]), language: 'c')

#
# Dependencies
#

bdwgc = dependency('bdw-gc', required: true)
readline = dependency('readline', required: true)

#
# Executables
#

ploy_include = include_directories('include')
ploy_includes = files(
  'include/ploy/core.h',
  'include/ploy/evaluator.h',
  'include/ploy/math.h',
  'include/ploy/printer.h',
  'include/ploy/reader.h',
  'include/ploy/type.h',
)

ploy_main = files('src/main.c')
ploy_src = files(
  'src/core.c',
  'src/evaluator.c',
  'src/math.c',
  'src/printer.c',
  'src/reader.c',
  'src/type.c',
)

executable('ploy',
  dependencies: [bdwgc, readline],
  include_directories: ploy_include,
  install: true,
  sources: [ploy_src, ploy_main],
)

#
# Tests
#

ploy_tests = []
subdir('test')

#
# Lints
#

run_target('clang-format', command: [
  'clang-format', '--dry-run', '--verbose', '--Werror',
  ploy_includes, ploy_src, ploy_main, ploy_tests])

run_target('clang-tidy', command: [
  'clang-tidy', '--quiet', '-p', 'builddir/',
  ploy_includes, ploy_src, ploy_main, ploy_tests])
