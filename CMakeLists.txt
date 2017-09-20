cmake_minimum_required( VERSION 3.0)

project( mulle-vararg C)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/mulle-configuration/cmake)
message(STATUS "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  include( Debug)
else()
  include( Release)
endif()


include( CMakeSourcesAndHeaders.txt)
include( CMakeDependencies.txt)


set( PUBLIC_HEADERS
${HEADERS}
CMakeDependencies.txt
)


add_library( mulle_vararg
${SOURCES}
${HEADERS}
)


set( STANDALONE_BASE_NAME "mulle_vararg")
set( STANDALONE_NAME "mulle_vararg_standalone")
set( STANDALONE_DEFINITIONS ${MULLE_VARARG_DEFINITIONS})
set( STANDALONE_ALL_LOAD_LIBRARIES
$<TARGET_FILE:mulle_vararg>
${DEPENDENCY_LIBRARIES}
)

include( Standalone)

INSTALL( TARGETS mulle_vararg mulle_vararg_standalone DESTINATION "lib")
INSTALL( FILES ${PUBLIC_HEADERS} DESTINATION "include/mulle_vararg")

include( MulleTest)


