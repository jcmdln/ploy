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
  meson_version: '>=0.46',
  version: '0.0.0',
)

#
# Compilation
#

compiler = meson.get_compiler('c', native: true)
compiler_args = []

compiler_args += [
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
  '-Wno-unused-but-set-parameter',
  '-Wno-unused-parameter',
  '-Wno-unused-result',
  '-Wno-unused-variable',
]

if compiler.get_id().startswith('clang')
  compiler_args += [
    '-Werror=ignored-qualifiers',
    '-Werror=unreachable-code-break',
    '-Werror=unreachable-code-return',
  ]
elif compiler.get_id().startswith('gcc')
  compiler_args += [
    '-Werror=discarded-qualifiers',
    '-Werror=switch-unreachable',
  ]
endif

add_project_arguments(compiler.get_supported_arguments(compiler_args), language: 'c')

#
# Dependencies
#

bdw_gc = dependency('bdw-gc', required: true)
readline = dependency('readline', required: true)

#
# Executables
#

ploy_includes = include_directories('include')
ploy_sources = []
subdir('src')

executable(
  'ploy',
  dependencies: [bdw_gc, readline],
  include_directories: [ploy_includes],
  install: true,
  sources: [ploy_sources, src_main_c],
)

#
# Tests
#

# FIXME: https://github.com/mesonbuild/meson/issues/2518
# FIXME: https://github.com/mesonbuild/meson/pull/6511
if get_option('test')
  subdir('test')
endif
