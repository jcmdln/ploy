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
        'c_std=c11',
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

cc = meson.get_compiler('c', native: true)

ploy_opts = [
    '-fno-omit-frame-pointer',
    '-Werror=trigraphs',
    '-Werror=vla',
    '-Wno-error=pedantic',
    '-Wno-error=uninitialized',
    '-Wno-error=unused-but-set-parameter',
    '-Wno-error=unused-parameter',
    '-Wno-error=unused-variable',
]

if cc.get_id().startswith('clang')
    ploy_opts += [
        '-Werror=unreachable-code-break',
        '-Werror=unreachable-code-return',
    ]
elif cc.get_id().startswith('gcc')
    ploy_opts += [
        '-Werror=switch-unreachable',
    ]
endif

if get_option('buildtype').startswith('debug')
    ploy_opts += [
        '-fsanitize=float-cast-overflow',
        '-fsanitize=float-divide-by-zero',
        '-fsanitize=integer-divide-by-zero',
        '-fsanitize=signed-integer-overflow',
        '-fsanitize=unsigned-integer-overflow',
    ]
endif

foreach opt : ploy_opts
    if cc.has_argument(opt)
        add_project_arguments(opt, language: 'c')
    endif
endforeach

ploy_sources = []
subdir('src')

executable(
    'ploy',
    dependencies: [
        dependency('bdw-gc', required: true),
        dependency('readline', required: true),
    ],
    include_directories: [
        include_directories('include')
    ],
    install: true,
    sources: ploy_sources,
)
