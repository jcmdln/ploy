# SPDX-License-Identifier: ISC

project(
    'ploy',
    'c', 'cpp',
    default_options: [
        'b_colorout=always',
        'b_lto=false',
        'b_lto_mode=thin',
        'b_pie=false',
        'b_sanitize=none',
        'buildtype=release',
        'c_std=c18',
        'cpp_eh=none',
        'cpp_std=c++20',
        'default_library=shared',
        'optimization=2',
        'strip=false',
        'warning_level=3',
        'werror=false',
    ],
    license: 'ISC',
    meson_version: '>=0.57',
    version: '0.0.0',
)

cpp = meson.get_compiler('cpp', native: true)

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

if cpp.get_id().startswith('clang')
    ploy_opts += [
        '-Werror=unreachable-code-break',
        '-Werror=unreachable-code-return',
        '-Wno-writable-strings',
    ]
elif cpp.get_id().startswith('gcc')
    ploy_opts += [
        '-Werror=switch-unreachable',
        '-Wno-missing-field-initializers',
        '-Wno-write-strings',
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
    if cpp.has_argument(opt)
        add_project_arguments(opt, language: 'cpp')
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
    sources: ploy_sources,
)
