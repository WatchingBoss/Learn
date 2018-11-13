# CMakeList.txt : CMake project for neural_net_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Define MACRO
add_definitions( -DCMAKE_PROJECT_DIR_PATH="${PROJECT_SOURCE_DIR}" )

# Project's sources and headers
file(GLOB P_SOURCES ./*.cpp)
file(GLOB P_HEADERS ./*.h)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${P_SOURCES} ${P_HEADERS})

# TODO: Add tests and install targets if needed.
