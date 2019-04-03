cmake_minimum_required(VERSION 3.2)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "ppc")
set(CMAKE_CROSSCOMPILING 1)

# Find DEVKITPRO
if(NOT DEFINED ENV{DEVKITPRO})
   message(FATAL_ERROR "You must have defined DEVKITPRO before calling cmake.")
endif()

set(DEVKITPRO $ENV{DEVKITPRO})

if(NOT DEFINED ENV{DEVKITPPC})
   set(DEVKITPPC $ENV{DEVKITPRO}/devkitPPC)
else()
   set(DEVKITPPC $ENV{DEVKITPPC})
endif()

if(NOT DEFINED ENV{WUT_ROOT})
   set(WUT_ROOT $ENV{DEVKITPRO}/wut)
else()
   set(WUT_ROOT $ENV{WUT_ROOT})
endif()

# Find elf2rpl
find_program(ELF2RPL_BIN
   NAMES elf2rpl
)

if(NOT ELF2RPL_BIN)
   message(FATAL_ERROR "Could not find elf2rpl")
endif()

# Find rplexportgen
find_program(RPLEXPORTGEN_BIN
   NAMES rplexportgen
)

if(NOT RPLEXPORTGEN_BIN)
   message(FATAL_ERROR "Could not find rplexportgen")
endif()

set(CMAKE_ASM_COMPILER     "powerpc-eabi-gcc"   CACHE PATH "")
set(CMAKE_C_COMPILER       "powerpc-eabi-gcc"   CACHE PATH "")
set(CMAKE_CXX_COMPILER     "powerpc-eabi-g++"   CACHE PATH "")
set(CMAKE_LINKER           "powerpc-eabi-ld"    CACHE PATH "")
set(CMAKE_AR               "powerpc-eabi-ar"    CACHE PATH "")
set(CMAKE_STRIP            "powerpc-eabi-strip" CACHE PATH "")

set(WUT_C_FLAGS            "-mcpu=750 -meabi -mhard-float -Wl,-q -D__WIIU__ -D__WUT__ -isystem \"${WUT_ROOT}/include\"")
set(CMAKE_C_FLAGS          "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-z,nocopyreloc -T \"${WUT_ROOT}/share/wut.ld\" \"-L${WUT_ROOT}/lib\"" CACHE STRING "")

# Setup root to exclude host system headers + libraries
set(CMAKE_FIND_ROOT_PATH "${DEVKITPPC}" "${DEVKITPRO}/tools/bin" "${DEVKITPRO}/portlibs/wiiu" "${DEVKITPRO}/portlibs/ppc" "${WUT_ROOT}/share")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Tools
set(WUT_ELF2RPL "${ELF2RPL_BIN}" CACHE PATH "")
set(WUT_RPLEXPORTGEN "${RPLEXPORTGEN_BIN}" CACHE PATH "")

# Flags
set(WUT TRUE)
set(WIIU TRUE)

# There is no shared lib support in devkitPPC
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available")
