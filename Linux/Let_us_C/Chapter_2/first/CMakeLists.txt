cmake_minimum_required(VERSION 3.9)
project(first C)

set(CMAKE_C_STANDARD 99)

add_executable(first main.c)

set(BUILD_1 exercise.c)
set(SOURCE_FILES_1 exercise.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

target_link_libraries(first m)
target_link_libraries(exercise.c m)