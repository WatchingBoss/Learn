cmake_minimum_required (VERSION 3.6)

project (go)

find_package(OpenGL REQUIRED)

if(MSVC)
  #  add_compile_options(/W3 /Wall /WX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Werror -Wall -Wpedantic -g")
endif()

if(WIN32)
  set (THIRD_PART_LIBS "D:/Documents/libs/third_part_libs/")
elseif(UNIX AND NOT APPLE)
  set (THIRD_PART_LIBS "/media/ubu/data/Documents/libs/third_part_libs/")
endif()

# Path to header files
include_directories (${THIRD_PART_LIBS})

# Third part libraries
add_library(ThirdPartLib
  ${THIRD_PART_LIBS}imgui/imgui.cpp
  ${THIRD_PART_LIBS}imgui/imgui_demo.cpp
  ${THIRD_PART_LIBS}imgui/imgui_draw.cpp
  ${THIRD_PART_LIBS}imgui/imgui_impl_glfw.cpp
  ${THIRD_PART_LIBS}imgui/imgui_impl_opengl3.cpp)
##add_subdirectory(${THIRD_PART_LIBS}/imgui)

# Required for OpenGL
add_library(ForOpenGL INTERFACE)
if(MSVC)
  set (FOR_OPEN_GL "D:/Documents/libs/open_gl/")
  include_directories(${FOR_OPEN_GL}include)
  target_link_libraries(ForOpenGL INTERFACE
    opengl32.lib
	${FOR_OPEN_GL}lib/glew32s.lib
	${FOR_OPEN_GL}lib/glfw3.lib)
else()
  target_link_libraries(ForOpenGL INTERFACE glfw GL GLEW)
endif()

file(GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/inc/*.hpp)
file(GLOB PROJECT_SHADERS ${PROJECT_SOURCE_DIR}/shader/*.vert ${PROJECT_SOURCE_DIR}/shader/*.frag)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SHADERS})
target_link_libraries (${PROJECT_NAME} PUBLIC ThirdPartLib ForOpenGL)