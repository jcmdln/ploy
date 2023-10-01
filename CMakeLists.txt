# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>

cmake_minimum_required(VERSION 3.13)
project(Ploy LANGUAGES C VERSION 0.0.0)

add_executable(ploy
    src/core.c
    src/evaluator.c
    src/main.c
    src/math.c
    src/printer.c
    src/reader.c
    src/type.c
)

target_include_directories(ploy
PUBLIC
    ${PROJECT_SOURCE_DIR}/include
PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

#
# Compilation
#

target_compile_features(ploy
PRIVATE
    c_std_11
)

target_compile_options(ploy
PRIVATE
    -flto
    -fshort-wchar -fstrict-aliasing -funsigned-char
    -Wall -Wextra -pedantic
    -Werror=cast-qual
    -Werror=implicit-int
    -Werror=strict-prototypes
    -Werror=switch
    -Werror=vla
    -Werror=write-strings
    -Wno-error=pedantic
    -Wno-error=unused-but-set-parameter
    -Wno-error=unused-parameter
    -Wno-error=unused-result
    -Wno-error=unused-variable
)

target_link_options(ploy
PRIVATE
    -flto
)

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(ploy
    PRIVATE
        -Werror=ignored-qualifiers
        -Werror=unreachable-code-break
        -Werror=unreachable-code-return
    )
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU")
    target_compile_options(ploy
    PRIVATE
        -Werror=discarded-qualifiers
        -Werror=switch-unreachable
    )
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(ploy
    PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )
    target_link_options(ploy
    PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )

    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_compile_options(ploy
        PRIVATE
            -fsanitize=float-divide-by-zero
            -fsanitize=implicit-conversion
            -fsanitize=integer
            -fsanitize=nullability
        )
    elseif (CMAKE_C_COMPILER_ID MATCHES "GNU")
        target_compile_options(ploy
        PRIVATE
            -fsanitize=pointer-compare
            -fsanitize=pointer-subtract
        )
    endif()
endif()

#
# Dependencies
#

# https://github.com/ivmai/bdwgc
# TODO(jcmdln): Find something smaller? Build my own GC?
# TODO(jcmdln): Read https://github.com/orangeduck/tgc
# TODO(jcmdln): Read https://github.com/bullno1/ugc
# TODO(jcmdln): Read https://github.com/nyuichi/gc.h
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/bdwgc)

# https://github.com/jart/bestline
add_library(bestline SHARED ${PROJECT_SOURCE_DIR}/vendor/bestline/bestline.c)
target_include_directories(bestline PUBLIC ${PROJECT_SOURCE_DIR}/vendor/bestline)

target_link_libraries(ploy
PRIVATE
    bestline
    gc
)

#
# Lints
#

add_custom_target(clang-format
COMMAND
    clang-format --dry-run --verbose --Werror
        ${PROJECT_SOURCE_DIR}/include/**/*.h
        ${PROJECT_SOURCE_DIR}/src/*.c
)

add_custom_target(clang-tidy
COMMAND
    clang-tidy -p ${PROJECT_SOURCE_DIR}/build/
        ${PROJECT_SOURCE_DIR}/include/**/*.h
        ${PROJECT_SOURCE_DIR}/src/*.c
)
