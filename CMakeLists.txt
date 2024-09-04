cmake_minimum_required(VERSION 3.13)
project(Ploy LANGUAGES C VERSION 0.0.0)

add_executable(ploy src/main.c src/core.c src/eval.c src/math.c src/read.c)
target_compile_features(ploy PRIVATE c_std_11)
target_compile_options(ploy PRIVATE -DPLOY_VERSION=\"${CMAKE_PROJECT_VERSION}\")
target_include_directories(ploy PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

#
# Compilation
#

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
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

	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(ploy PRIVATE -fsanitize=address,undefined)
		target_link_options(ploy PRIVATE -fsanitize=address,undefined)
	endif()
endif()

#
# Dependencies
#

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(bdwgc REQUIRED IMPORTED_TARGET bdw-gc>=8)
	pkg_check_modules(readline REQUIRED IMPORTED_TARGET readline>=8)
	target_link_libraries(ploy PUBLIC PkgConfig::bdwgc PkgConfig::readline)
endif()

#
# Lints
#

add_custom_target(clang-format
COMMAND
	clang-format --dry-run --verbose --Werror
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_custom_target(clang-tidy
COMMAND
	clang-tidy -p "${CMAKE_CURRENT_SOURCE_DIR}/build"
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
