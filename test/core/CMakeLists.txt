add_executable(car car.c ../../src/core.c)
target_include_directories(car PUBLIC ../../include)
target_link_libraries(car PkgConfig::bdwgc)
add_test(NAME core_car COMMAND car)


add_executable(cdr cdr.c ../../src/core.c)
target_include_directories(cdr PUBLIC ../../include)
target_link_libraries(cdr PkgConfig::bdwgc)
add_test(NAME core_cdr COMMAND cdr)


add_executable(cons cons.c ../../src/core.c)
target_include_directories(cons PUBLIC ../../include)
target_link_libraries(cons PkgConfig::bdwgc)
add_test(NAME core_cons COMMAND cons)


add_executable(read read.c ../../src/core.c ../../src/read.c)
target_include_directories(read PUBLIC ../../include)
target_link_libraries(read PkgConfig::bdwgc)
add_test(NAME core_read COMMAND read)


add_executable(reverse reverse.c ../../src/core.c ../../src/read.c)
target_include_directories(reverse PUBLIC ../../include)
target_link_libraries(reverse PkgConfig::bdwgc)
add_test(NAME core_reverse COMMAND reverse)
