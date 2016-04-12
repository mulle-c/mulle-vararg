cmake_minimum_required (VERSION 3.0)

project (mulle-vararg)

#
# dont forget to wipe all cmake produced files before
# changing this
#

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
   set (CMAKE_C_FLAGS "-Wno-parantheses")
endif()

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -DDEBUG -DMULLE_ATOMIC_TRACE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -DNDEBUG")

set(HEADERS
src/mulle_align.h
src/mulle_vararg.h
)

add_library(mulle_vararg
src/mulle_vararg.c
)


INSTALL(TARGETS mulle_vararg DESTINATION "lib")
INSTALL(FILES ${HEADERS} DESTINATION "include/mulle_vararg")


