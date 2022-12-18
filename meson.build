# SPDX-License-Identifier: ISC
#
# Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

project(
  'ploy',
  'c',
  default_options: [
    'b_colorout=always',
    'b_lto=false',
    'b_lto_mode=thin',
    'b_pie=false',
    'b_sanitize=none',
    'buildtype=release',
    'c_std=c17',
    'default_library=shared',
    'optimization=2',
    'strip=false',
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

opts = [
  '-fshort-wchar',
  '-fstrict-aliasing',
  '-funsigned-char',
  '-Werror=trigraphs',
  '-Werror=vla',
  '-Werror=write-strings',
  '-Wno-error=pedantic',
  '-Wno-error=uninitialized',
  '-Wno-error=unused-but-set-parameter',
  '-Wno-error=unused-parameter',
  '-Wno-error=unused-variable',
]

if compiler.get_id().startswith('clang')
  opts += [
    '-Werror=unreachable-code-break',
    '-Werror=unreachable-code-return',
  ]
elif compiler.get_id().startswith('gcc')
  opts += [
    '-Werror=discarded-qualifiers',
    '-Werror=switch-unreachable',
  ]
endif

if get_option('buildtype').startswith('debug')
  opts += [
    '-fno-omit-frame-pointer',
    '-fsanitize=float-cast-overflow',
    '-fsanitize=float-divide-by-zero',
    '-fsanitize=integer-divide-by-zero',
    '-fsanitize=pointer-overflow',
    '-fsanitize=shadow-call-stack',
    '-fsanitize=signed-integer-overflow',
    '-fsanitize=unsigned-integer-overflow',
  ]
endif

foreach opt : opts
  if compiler.has_argument(opt)
    add_project_arguments(opt, language: 'c')
  endif
endforeach

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
