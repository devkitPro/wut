cmake_minimum_required(VERSION 3.2)
project(wut)
include(ExternalProject)

option(WUT_BUILD_DOCS "Build documentation" OFF)
option(WUT_BUILD_TOOLS "Build tools" ON)
option(WUT_BUILD_PPC "Build PPC code using devkitPPC" ON)

set(WUT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(WUT_STAGING "${CMAKE_BINARY_DIR}/staging")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

if(WUT_BUILD_DOCS)
   add_subdirectory(docs)
endif()

if(WUT_BUILD_TOOLS)
   add_subdirectory(tools)
endif()

if(WUT_BUILD_PPC)
   if(NOT WUT_BUILD_TOOLS)
      message(FATAL_ERROR "WUT_BUILD_PPC requires WUT_BUILD_TOOLS.")
   endif()

   set(WUT_TOOLCHAIN "${CMAKE_CURRENT_SOURCE_DIR}/share/wut.toolchain.cmake")

   externalproject_add(cafe
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cafe"
      CMAKE_GENERATOR "Unix Makefiles"
      INSTALL_DIR "${WUT_STAGING}"
      CMAKE_CACHE_ARGS
         -DWUT_ROOT:filepath=${WUT_ROOT}
         -DWUT_RPLIMPORTGEN:filepath=$<TARGET_FILE:rplimportgen>
         -DCMAKE_TOOLCHAIN_FILE:filepath=${WUT_TOOLCHAIN}
         -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      DEPENDS rplimportgen
      BUILD_ALWAYS 1)

   externalproject_add(libraries
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries"
      CMAKE_GENERATOR "Unix Makefiles"
      INSTALL_DIR "${WUT_STAGING}"
      CMAKE_CACHE_ARGS
         -DWUT_ROOT:filepath=${WUT_ROOT}
         -DCMAKE_TOOLCHAIN_FILE:filepath=${WUT_TOOLCHAIN}
         -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      BUILD_ALWAYS 1)
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
   FILES_MATCHING PATTERN "*.h*")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/share/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/share")

install(DIRECTORY "${CMAKE_BINARY_DIR}/staging/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}")
