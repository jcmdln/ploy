# SPDX-License-Identifier: ISC
#
# Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

project(
  'ploy',
  'c',
  default_options: [
    'buildtype=release',
    'c_std=c17',
    'warning_level=3',
    'werror=false',
  ],
  license: 'ISC',
  meson_version: '>=0.53',
  version: '0.0.0',
)

#
# Compilation
#

compiler = meson.get_compiler('c', native: true)

includes = include_directories('include')
sources = []
subdir('src')

add_project_arguments(compiler.get_supported_arguments([
  '-fshort-wchar',
  '-fstrict-aliasing',
  '-funsigned-char',
  '-fno-digraphs',
  '-fno-trigraphs',
  '-Werror=cast-qual',
  '-Werror=implicit-int',
  '-Werror=strict-prototypes',
  '-Werror=vla',
  '-Werror=write-strings',
  '-Wno-error=pedantic',
  '-Wno-error=unused-but-set-parameter',
  '-Wno-error=unused-parameter',
  '-Wno-error=unused-result',
  '-Wno-error=unused-variable',
]), language: 'c')

if compiler.get_id().startswith('clang')
  add_project_arguments(compiler.get_supported_arguments([
    '-Werror=ignored-qualifiers',
    '-Werror=unreachable-code-break',
    '-Werror=unreachable-code-return',
  ]), language: 'c')
elif compiler.get_id().startswith('gcc')
  add_project_arguments(compiler.get_supported_arguments([
    '-Werror=discarded-qualifiers',
    '-Werror=switch-unreachable',
  ]), language: 'c')
endif

if get_option('buildtype').startswith('debug')
  sanitizers = [
    '-fsanitize=address',
    '-fsanitize=undefined',
  ]
  add_project_arguments(compiler.get_supported_arguments(sanitizers), language: 'c')
  add_project_link_arguments(compiler.get_supported_link_arguments(sanitizers), language: 'c')
endif

#
# Dependencies
#

bdw_gc = dependency('bdw-gc', required: true)
readline = dependency('readline', required: true)

#
# Executables
#

executable(
  'ploy',
  dependencies: [bdw_gc, readline],
  include_directories: includes,
  install: true,
  sources: sources,
)

#
# Tests
#

# FIXME: https://github.com/mesonbuild/meson/issues/2518
# FIXME: https://github.com/mesonbuild/meson/pull/6511
if get_option('test')
  subdir('test')
endif
