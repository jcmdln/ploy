add_executable(add add.c ../../src/core.c ../../src/math.c)
target_include_directories(add PUBLIC ../../include)
target_link_libraries(add PkgConfig::bdwgc)
add_test(NAME math_add COMMAND add)


add_executable(divide divide.c ../../src/core.c ../../src/math.c)
target_include_directories(divide PUBLIC ../../include)
target_link_libraries(divide PkgConfig::bdwgc)
add_test(NAME math_divide COMMAND divide)


add_executable(multiply multiply.c ../../src/core.c ../../src/math.c)
target_include_directories(multiply PUBLIC ../../include)
target_link_libraries(multiply PkgConfig::bdwgc)
add_test(NAME math_multiply COMMAND multiply)


add_executable(subtract subtract.c ../../src/core.c ../../src/math.c)
target_include_directories(subtract PUBLIC ../../include)
target_link_libraries(subtract PkgConfig::bdwgc)
add_test(NAME math_subtract COMMAND subtract)
