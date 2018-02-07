cmake_minimum_required(VERSION 3.9)
project(site_creator C)

set(CMAKE_C_STANDARD 99)

add_executable(site_creator main.c template.h)

set(BUILD_1 example.c)
set(SOURCE_FILES_1 example.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})