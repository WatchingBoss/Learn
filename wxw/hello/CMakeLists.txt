cmake_minimum_required (VERSION 3.6)

project (go)

if(!MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wno-long-long \
-Wno-variadic-macros -fexceptions")
endif()

set (CMAKE_BUILD_TYPE Debug)

if(MSVC)
  find_package( wxWidgets COMPONENTS core base REQUIRED )
else()
  find_package( wxWidgets )
endif()

include( ${wxWidgets_USE_FILE} )

file( GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp )
file( GLOB INC ${PROJECT_SOURCE_DIR}/*.h )

add_executable( ${PROJECT_NAME} ${SRC} ${INC} )
target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES} )
