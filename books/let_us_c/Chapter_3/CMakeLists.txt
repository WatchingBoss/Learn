cmake_minimum_required(VERSION 3.9)
project(Chapter_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Chapter_3 main.c)

set(BUILD_1 exercise.c)
set(SOURCE_FILES_1 exercise.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

target_link_libraries(Chapter_3 m)
target_link_libraries(exercise.c m)