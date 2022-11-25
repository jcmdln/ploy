# SPDX-License-Identifier: ISC
#
# Copyright (c) 2022 Johnathan C Maudlin <jcmdln@gmail.com>

# Collect all source files other than 'main.c' so that tests can define their
# own `main` function.
test_sources = []
foreach file : sources
  target = join_paths(meson.project_source_root(), '@0@'.format(file))
  if not target.contains('main.c')
    test_sources += ''.join(target)
  endif
endforeach

subdir('printer')
subdir('reader')
