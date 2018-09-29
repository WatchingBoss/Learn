cmake_minimum_required(VERSION 3.9)
project(first C)

set(CMAKE_C_STANDARD 99)

add_executable(first main.c func_for_io.h)

set(BUILD_1 main.c)
set(SOURCE_FILES_1 main.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 just_for_fun.c)
set(SOURCE_FILES_2 just_for_fun.c)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

set(BUILD_3 some.c func_for_io.h)
set(SOURCE_FILES_3 some.c func_for_io.h)
add_executable(${BUILD_3} ${SOURCE_FILES_3})


target_link_libraries(some.c m)
target_link_libraries(first m)
target_link_libraries(just_for_fun.c m)