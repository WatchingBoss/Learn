cmake_minimum_required(VERSION 3.9)
project(Chapter_1_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Chapter_1_3 first.c)

set(BUILD_1 first.c)
set(SOURCE_FILES_1 first.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_1 my_create.c)
set(SOURCE_FILES_1 my_create.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})