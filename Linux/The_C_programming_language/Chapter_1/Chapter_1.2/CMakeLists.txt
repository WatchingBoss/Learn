cmake_minimum_required(VERSION 3.9)
project(Chapter_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Chapter_1 hello.c FahtoCel.c exercise_1_3.c exercise_1_4.c)

set(BUILD_1 hello.c)
set(SOURCE_FILES_1 hello.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 FahtoCel.c)
set(SOURCE_FILES_2 FahtoCel.c)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

set(BUILD_2 exercise_1_3.c)
set(SOURCE_FILES_2 exercise_1_3.c)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

set(BUILD_2 exercise_1_4.c)
set(SOURCE_FILES_2 exercise_1_4.c)
add_executable(${BUILD_2} ${SOURCE_FILES_2})