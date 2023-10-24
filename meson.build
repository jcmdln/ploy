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

bdwgc = dependency('bdw-gc', required: true)
readline = dependency('readline', required: true)

add_project_arguments(
  '-DPLOY_VERSION="@0@"'.format(meson.project_version()),
  compiler.get_supported_arguments([
    '-fshort-wchar',
    '-fstrict-aliasing',
    '-funsigned-char',
    '-Wno-implicitly-unsigned-literal',
    '-Werror=cast-qual',
    '-Werror=implicit-int',
    '-Werror=strict-prototypes',
    '-Werror=vla',
    '-Werror=write-strings',
  ]),
  language: 'c'
)

#
# Executables
#

include = include_directories('include')
includes = files(
  'include/ploy/core.h',
  'include/ploy/evaluator.h',
  'include/ploy/math.h',
  'include/ploy/printer.h',
  'include/ploy/reader.h',
  'include/ploy/type.h',
)

main = files('source/main.c')
sources = files(
  'source/core.c',
  'source/evaluator.c',
  'source/math.c',
  'source/printer.c',
  'source/reader.c',
)

executable('ploy',
  dependencies: [bdwgc, readline],
  include_directories: include,
  install: true,
  sources: [sources, main],
)

#
# Tests
#

tests = []
subdir('test')

#
# Lints
#

run_target('clang-format', command: [
  'clang-format', '--dry-run', '--verbose', '--Werror',
  includes, sources, main, tests
])

run_target('clang-tidy', command: [
  'clang-tidy', '--quiet', '-p', 'builddir/',
  includes, sources, main, tests
])
