cmake_minimum_required (VERSION 3.0)

project (mulle-vararg)

cmake_policy(SET CMP0054 NEW)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/mulle-configuration)
message(STATUS "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  include( Debug)
else()
  include( Release)
endif()

set(HEADERS
src/mulle_align.h
src/mulle_vararg.h
)

set( SOURCES
src/mulle_vararg.c
)

add_library(mulle_vararg
${SOURCES}
)


INSTALL(TARGETS mulle_vararg DESTINATION "lib")
INSTALL(FILES ${HEADERS} DESTINATION "include/mulle_vararg")


