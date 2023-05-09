# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

project('ploy', 'c',
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

compiler_args = [
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

# https://releases.llvm.org/7.0.0/tools/clang/docs/UndefinedBehaviorSanitizer.html
# https://gcc.gnu.org/onlinedocs/gcc-8.1.0/gcc/Instrumentation-Options.html
if get_option('b_sanitize').contains('undefined')
  compiler_args += [
    '-fsanitize=float-cast-overflow',
    '-fsanitize=float-divide-by-zero',
  ]

  if compiler.get_id().startswith('clang')
    compiler_args += ['-fsanitize=integer']
  # elif compiler.get_id().startswith('gcc')
  #   compiler_args += []
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

ploy_includes = include_directories('include')
ploy_sources = []
subdir('src')

executable('ploy',
  dependencies: [bdwgc, readline],
  include_directories: include_directories('include'),
  install: true,
  sources: [ploy_sources, src_main_c],
)

#
# Lints
#

lint_includes = files(
  'include/ploy/reader/lexer.h',
  'include/ploy/reader/parser.h',
  'include/ploy/reader/token.h',
  'include/ploy/ploy.h',
  'include/ploy/printer.h',
  'include/ploy/reader.h',
)

run_target('clang-format',
  command: ['clang-format', '--dry-run', '--Werror', lint_includes, ploy_sources, src_main_c]
)

run_target('clang-tidy',
  command: ['clang-tidy', '-p', '.', lint_includes, ploy_sources, src_main_c]
)

#
# Tests
#

# FIXME: https://github.com/mesonbuild/meson/issues/2518
# FIXME: https://github.com/mesonbuild/meson/pull/6511
if get_option('test')
  subdir('test')
endif
