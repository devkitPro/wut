cmake_minimum_required(VERSION 3.2)
project(wut)
include(ExternalProject)

option(WUT_BUILD_DOCS "Build documentation" OFF)

set(DEVKITPPC $ENV{DEVKITPPC} CACHE STRING "Path to devkitPPC install")

# Check for DEVKITPPC
if(NOT DEVKITPPC)
    message(FATAL_ERROR "You must have defined DEVKITPPC before calling cmake.")
endif()

set(WUT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(WUT_TOOLCHAIN "${CMAKE_CURRENT_SOURCE_DIR}/share/wut.toolchain.cmake")
set(WUT_STAGING "${CMAKE_BINARY_DIR}/staging")

if(WUT_BUILD_DOCS)
   add_subdirectory(docs)
endif()

externalproject_add(tools
   SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools"
   INSTALL_DIR "${WUT_STAGING}"
   CMAKE_CACHE_ARGS
      -DCMAKE_C_COMPILER:string=${CMAKE_C_COMPILER}
      -DCMAKE_C_FLAGS:string=${CMAKE_C_FLAGS}
      -DCMAKE_CXX_COMPILER:string=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS:string=${CMAKE_CXX_FLAGS}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
   BUILD_ALWAYS 1)
externalproject_get_property(tools BINARY_DIR)
set(TOOLS_BINARY_DIR ${BINARY_DIR})

set(WUT_RPLGEN "${TOOLS_BINARY_DIR}/bin/wut-rplgen")

externalproject_add(cafe
   SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cafe"
   INSTALL_DIR "${WUT_STAGING}"
   CMAKE_CACHE_ARGS
      -DWUT_RPLGEN:filepath=${WUT_RPLGEN}
      -DWUT_ROOT:filepath=${WUT_ROOT}
      -DCMAKE_TOOLCHAIN_FILE:filepath=${WUT_TOOLCHAIN}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
   DEPENDS tools
   BUILD_ALWAYS 1)

externalproject_add(libraries
   SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries"
   INSTALL_DIR "${WUT_STAGING}"
   CMAKE_CACHE_ARGS
      -DWUT_ROOT:filepath=${WUT_ROOT}
      -DCMAKE_TOOLCHAIN_FILE:filepath=${WUT_TOOLCHAIN}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
   BUILD_ALWAYS 1)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
   FILES_MATCHING PATTERN "*.h*")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/share/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/share")

install(DIRECTORY "${CMAKE_BINARY_DIR}/staging/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}")
