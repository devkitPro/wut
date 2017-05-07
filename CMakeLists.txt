cmake_minimum_required(VERSION 3.2)
project(wut)
include(ExternalProject)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DEVKITPPC $ENV{DEVKITPPC} CACHE STRING "Path to devkitPPC install")

# Check for DEVKITPPC
if(NOT DEVKITPPC)
    message(FATAL_ERROR "You must have defined DEVKITPPC before calling cmake.")
endif()

add_subdirectory(src)
add_subdirectory(externals)
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
