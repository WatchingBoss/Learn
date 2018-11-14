# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("neural_net_cpp")

# Define MACRO
add_definitions( -DCMAKE_PROJECT_DIR_PATH="${PROJECT_SOURCE_DIR}" )

# Project's sources and headers
file(GLOB P_SOURCES ${PROJECT_SOURCE_DIR}/neural_net_cpp/*.cpp)
file(GLOB P_HEADERS ${PROJECT_SOURCE_DIR}/neural_net_cpp/*.h)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${P_SOURCES} ${P_HEADERS})

# TODO: Add tests and install targets if needed.
