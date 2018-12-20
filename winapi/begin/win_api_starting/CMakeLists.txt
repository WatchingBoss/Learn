cmake_minimum_required (VERSION 3.8)

project ("win")

# Macro definitions
set( COMPILE_TIME_RES )
#set( RUN_TIME_RES )
add_definitions( -DCOMPILE_TIME_RES_DEF ${COMPILE_TIME_RES} )
#add_definitions( -DRUN_TIME_RES_DEF ${RUN_TIME_RES} )

set(rc_flags "/l 0x809")
set(CMAKE_RC_FLAGS ${rc_flags})

file( GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp )
file( GLOB PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/*.h )

source_group( "Sources"	FILES ${PROJECT_SOURCES} )
source_group( "Headers" FILES ${PROJECT_HEADERS} )

set( TO_EXE ${PROJECT_SOURCES} ${PROJECT_HEADERS} )

if(MSVC)
  add_executable( ${PROJECT_NAME} WIN32 ${TO_EXE} )

  ENABLE_LANGUAGE( RC )
  set( SOURCES ${PROJECT_SOURCE_DIR}/resources.rc ${SOURCES} )
  #add_library( RESOURCES ${SOURCES} )
endif(MSVC)

target_link_libraries( ${PROJECT_NAME} ${SOURCES} )

# Copy resources
if(RUN_TIME_RES)
  if(MSVC)
    file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ 
	      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/ )
  endif(MSVC)
endif(RUN_TIME_RES)