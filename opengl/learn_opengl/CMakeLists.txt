cmake_minimum_required (VERSION 3.6)

set (PROGECT_NAME "go")
project (${PROGECT_NAME})

if(MSVC)
#  add_compile_options(/W3 /Wall /WX)
  add_compile_options(/W3)
else()
  add_compile_options(-W -Werror -Wall -g)
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
	${FOR_OPEN_GL}lib/glew32s.lib
	${FOR_OPEN_GL}lib/glfw3.lib
	opengl32.lib)
else()
  target_link_libraries(ForOpenGL INTERFACE glfw GL GLEW)
endif()

add_executable (${PROGECT_NAME} main.cpp)
target_link_libraries (${PROGECT_NAME} PUBLIC ForOpenGL ThirdPartLib)

