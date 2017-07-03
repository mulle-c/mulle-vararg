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


#
# standalone shared library (for tests)
#

if( MSVC)
  set( DEF_FILE mulle_vararg_standalone.def)
  set_source_files_properties( ${DEF_FILE} PROPERTIES HEADER_FILE_ONLY TRUE)
  set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
  set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEF:${DEF_FILE}")
  # /NODEFAULTLIB:MSVCRT")
endif()


add_library( mulle_vararg_standalone SHARED
src/mulle_vararg_standalone.c
${DEF_FILE}
)

add_dependencies( mulle_vararg_standalone mulle_vararg)


set( DEPENDENCY_LIBRARIES
)


if( MSVC)
   add_custom_command( OUTPUT ${DEF_FILE}
                       COMMAND mulle-mingw-dumpdef.bat -o "${DEF_FILE}" --prefix "mulle" ${DEPENDENCY_LIBRARIES} $<TARGET_FILE:mulle_vararg>
                       DEPENDS "${DEPENDENCY_LIBRARIES}" mulle_vararg
                       VERBATIM)
endif()


TARGET_LINK_LIBRARIES( mulle_vararg_standalone
${BEGIN_ALL_LOAD}
mulle_vararg
${DEPENDENCY_LIBRARIES}
${END_ALL_LOAD}
)


INSTALL( TARGETS mulle_vararg_standalone DESTINATION "lib")

