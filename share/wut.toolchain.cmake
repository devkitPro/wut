cmake_minimum_required(VERSION 3.2)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "ppc")
set(CMAKE_CROSSCOMPILING 1)

find_program(DEVKITPPC_GCC NAMES powerpc-eabi-gcc)
if(DEVKITPPC_GCC)
   get_filename_component(DEVKITPPC_BIN ${DEVKITPPC_GCC} DIRECTORY)
   get_filename_component(DEVKITPPC ${DEVKITPPC_BIN} DIRECTORY)
else()
   if(NOT DEFINED ENV{DEVKITPPC})
      message(FATAL_ERROR "You must have added DEVKITPPC to PATH or defined DEVKITPPC before calling cmake.")
   endif()
   set(DEVKITPPC $ENV{DEVKITPPC})
   set(DEVKITPPC_BIN "${DEVKITPPC}/bin")
endif()

if(NOT DEFINED ENV{WUT_ROOT})
   message(FATAL_ERROR "You must have defined WUT_ROOT before calling cmake.")
endif()

set(WUT_ROOT $ENV{WUT_ROOT})

set(CMAKE_ASM_COMPILER     "${DEVKITPPC_BIN}/powerpc-eabi-gcc"   CACHE PATH "")
set(CMAKE_C_COMPILER       "${DEVKITPPC_BIN}/powerpc-eabi-gcc"   CACHE PATH "")
set(CMAKE_CXX_COMPILER     "${DEVKITPPC_BIN}/powerpc-eabi-g++"   CACHE PATH "")
set(CMAKE_LINKER           "${DEVKITPPC_BIN}/powerpc-eabi-ld"    CACHE PATH "")
set(CMAKE_AR               "${DEVKITPPC_BIN}/powerpc-eabi-ar"    CACHE PATH "")
set(CMAKE_STRIP            "${DEVKITPPC_BIN}/powerpc-eabi-strip" CACHE PATH "")

set(WUT_C_FLAGS            "-mcpu=750 -meabi -mhard-float -Wl,-q -D__WIIU__ -D__WUT__")
set(CMAKE_C_FLAGS          "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-z,nocopyreloc -T \"${WUT_ROOT}/share/wut.ld\" \"-L${WUT_ROOT}/lib\"" CACHE STRING "")

# Include paths for wut
include_directories(BEFORE SYSTEM "${WUT_ROOT}/include")

# Setup root to exclude host system headers + libraries
set(CMAKE_FIND_ROOT_PATH "${DEVKITPPC}" "${WUT_ROOT}/bin" "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_PREFIX}/share")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Tools
set(WUT_ELF2RPL "${WUT_ROOT}/bin/elf2rpl" CACHE PATH "")
set(WUT_RPLEXPORTGEN "${WUT_ROOT}/bin/rplexportgen" CACHE PATH "")

# Flags
set(WUT TRUE)
set(WIIU TRUE)

# There is no shared lib support in devkitPPC
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available")
