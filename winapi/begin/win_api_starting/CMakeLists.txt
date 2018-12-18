cmake_minimum_required (VERSION 3.8)

project ("win")

file( GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp )
file( GLOB PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/*.h )

source_group( "Sources" FILES ${PROJECT_SOURCES} )
source_group( "Headers" FILES ${PROJECT_HEADERS} )

if(MSVC)
add_executable( ${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
endif(MSVC)
#target_link_libraries( ${PROJECT_NAME} )

# Copy resources
if(MSVC)
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/ )
endif(MSVC)
