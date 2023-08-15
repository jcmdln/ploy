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

compiler_args = [
  '-fshort-wchar',
  '-fstrict-aliasing',
  '-funsigned-char',
  '-fno-digraphs',
  '-fno-trigraphs',
  '-Werror=cast-qual',
  '-Werror=implicit-int',
  '-Werror=restrict',
  '-Werror=strict-prototypes',
  '-Werror=switch',
  '-Werror=vla',
  '-Werror=write-strings',
  '-Wno-error=pedantic',
  '-Wno-error=unused-but-set-parameter',
  '-Wno-error=unused-parameter',
  '-Wno-error=unused-result',
  '-Wno-error=unused-variable',
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

if get_option('b_sanitize').contains('address')
  if compiler.get_id().startswith('gcc')
    compiler_args += [
      '-fsanitize=pointer-compare',
      '-fsanitize=pointer-subtract',
    ]
  endif
endif

if get_option('b_sanitize').contains('undefined')
  if compiler.get_id().startswith('clang')
    compiler_args += ['-fsanitize=float-divide-by-zero']
    compiler_args += ['-fsanitize=implicit-conversion']
    compiler_args += ['-fsanitize=integer']
    compiler_args += ['-fsanitize=nullability']
  endif
endif

add_project_arguments(compiler.get_supported_arguments(compiler_args), language: 'c')

#
# Dependencies
#

bdwgc = dependency('bdw-gc', required: true)
readline = dependency('readline', required: true)

#
# Executables
#

ploy_include_dirs = include_directories('include')
ploy_include = files(
  'include/ploy/core.h',
  'include/ploy/type.h',
)

ploy_src_main = files('src/main.c')
ploy_src = files(
  'src/core.c',
  'src/math.c',
  'src/printer.c',
  'src/reader.c',
  'src/type.c',
)

executable('ploy',
  dependencies: [bdwgc, readline],
  include_directories: ploy_include_dirs,
  install: true,
  sources: [ploy_src, ploy_src_main],
)

#
# Tests
#

ploy_test = []
subdir('test')

#
# Lints
#

ploy_files = [] + ploy_include + ploy_src + ploy_src_main + ploy_test

run_target('clang-format', command: ['clang-format', '--dry-run', '--Werror', ploy_files])
run_target('clang-tidy', command: ['clang-tidy', '-p', '.', ploy_files])
