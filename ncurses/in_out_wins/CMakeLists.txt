cmake_minimum_required( VERSION 3.6 )

project (go)

if(!MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wno-long-long \
-Wno-variadic-macros -fexceptions")
endif()

add_library( TUI INTERFACE )
target_link_libraries( TUI INTERFACE -lncurses )

file( GLOB PROG ${PROJECT_SOURCE_DIR}/main.cpp )

add_executable( ${PROJECT_NAME}  ${PROG} )
target_link_libraries( ${PROJECT_NAME} TUI )
