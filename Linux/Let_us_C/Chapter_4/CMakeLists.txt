cmake_minimum_required(VERSION 3.9)
project(Chapter_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Chapter_4 main.c)

set(BUILD_1 exercise.c)
set(SOURCE_FILES_1 exercise.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 main.c)
set(SOURCE_FILES_2 main.c)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

target_link_libraries(Chapter_4 m)
target_link_libraries(exercise.c m)
