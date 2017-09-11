cmake_minimum_required (VERSION 3.0)

project (mulle-vararg C)

cmake_policy(SET CMP0054 NEW)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/mulle-configuration/cmake)
message(STATUS "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  include( Debug)
else()
  include( Release)
endif()

include( CMakeSourcesAndHeaders.txt)


add_library( mulle_vararg
${SOURCES}
)


set( STANDALONE_BASE_NAME "mulle_vararg")
set( STANDALONE_NAME "mulle_vararg_standalone")

set( TARGET_ALL_LOAD_LIBRARIES
$<TARGET_FILE:mulle_vararg>
${DEPENDENCY_LIBRARIES}
)

include( Standalone)

INSTALL( TARGETS  DESTINATION "lib")
INSTALL(TARGETS mulle_vararg mulle_vararg_standalone DESTINATION "lib")
INSTALL(FILES ${HEADERS} DESTINATION "include/mulle_vararg")


