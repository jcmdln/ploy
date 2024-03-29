cmake_minimum_required(VERSION 3.13)
project(Ploy LANGUAGES C VERSION 0.0.0)

add_executable(ploy src/main.c src/core.c src/eval.c src/math.c src/read.c)
target_compile_options(ploy PRIVATE -DPLOY_VERSION=\"${CMAKE_PROJECT_VERSION}\")
target_include_directories(ploy PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

#
# Compilation
#

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

target_compile_features(ploy PRIVATE c_std_11)
target_compile_options(ploy PRIVATE
	-fshort-wchar -fstrict-aliasing -funsigned-char
	-Wall -Wextra -pedantic
	-Werror=cast-qual
	-Werror=conversion
	-Werror=implicit-int
	-Werror=strict-prototypes
	-Werror=switch
	-Werror=vla
	-Werror=write-strings
)

option(PLOY_LTO "Build ploy with link-time optimization" OFF)
if(PLOY_LTO)
	target_compile_options(ploy PRIVATE -flto)
	target_link_options(ploy PRIVATE -flto)
endif()

option(PLOY_USE_ASAN "Build ploy with AddressSanitizer" OFF)
if(PLOY_USE_ASAN)
	target_compile_options(ploy PRIVATE -fsanitize=address,undefined)
	target_link_options(ploy PRIVATE -fsanitize=address,undefined)
endif()

option(PLOY_USE_TSAN "Build ploy with ThreadSanitizer" OFF)
if(PLOY_USE_TSAN)
	target_compile_options(ploy PRIVATE -fsanitize=thread,undefined)
	target_link_options(ploy PRIVATE -fsanitize=thread,undefined)
endif()

#
# Dependencies
#

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(bdwgc    REQUIRED IMPORTED_TARGET bdw-gc>=8)
	pkg_check_modules(readline REQUIRED IMPORTED_TARGET readline>=8)
	target_link_libraries(ploy PUBLIC PkgConfig::bdwgc PkgConfig::readline)
endif()

#
# Lints
#

add_custom_target(clang-format
COMMAND clang-format --dry-run --verbose --Werror
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_custom_target(clang-tidy
COMMAND clang-tidy -p "${CMAKE_CURRENT_SOURCE_DIR}/build"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

#
# Tests
#

if(CMAKE_PROJECT_NAME STREQUAL Ploy)
	include(CTest)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()
