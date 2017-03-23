cmake_minimum_required(VERSION 3.2)
project(wut)
include(ExternalProject)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DEVKITPPC $ENV{DEVKITPPC} CACHE STRING "Path to devkitPPC install")

# Check for DEVKITPPC
if(NOT DEVKITPPC)
    message(FATAL_ERROR "You must have defined DEVKITPPC before calling cmake.")
endif()

externalproject_add(crt
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/crt"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

externalproject_add(rpl
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/rpl"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

add_subdirectory(tools)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
    FILES_MATCHING PATTERN "*.h*")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/cmake/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/rules/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/rules")

install(DIRECTORY "${CMAKE_BINARY_DIR}/staging/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}")
