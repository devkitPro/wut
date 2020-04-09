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

# Setup root to exclude host system headers + libraries
set(CMAKE_FIND_ROOT_PATH
   "${DEVKITPPC}"
   "${DEVKITPPC}/powerpc-eabi"
   "${DEVKITPRO}/tools"
   "${DEVKITPRO}/portlibs/wiiu"
   "${DEVKITPRO}/portlibs/ppc"
   "${WUT_ROOT}/share")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set pkg-config for the same
set(PKG_CONFIG_EXECUTABLE "${DEVKITPRO}/portlibs/wiiu/bin/powerpc-eabi-pkg-config")

# Find compilers
find_program(DEVKITPPC_GCC NAMES powerpc-eabi-gcc HINTS "${DEVKITPPC}/bin")
if(NOT DEVKITPPC_GCC)
   message(FATAL_ERROR "Could not find powerpc-eabi-gcc")
endif()

find_program(DEVKITPPC_GPP NAMES powerpc-eabi-g++ HINTS "${DEVKITPPC}/bin")
if(NOT DEVKITPPC_GPP)
   message(FATAL_ERROR "Could not find powerpc-eabi-g++")
endif()

find_program(DEVKITPPC_LD NAMES powerpc-eabi-ld HINTS "${DEVKITPPC}/bin")
if(NOT DEVKITPPC_LD)
   message(FATAL_ERROR "Could not find powerpc-eabi-ld")
endif()

find_program(DEVKITPPC_AR NAMES powerpc-eabi-ar HINTS "${DEVKITPPC}/bin")
if(NOT DEVKITPPC_AR)
   message(FATAL_ERROR "Could not find powerpc-eabi-ar")
endif()

find_program(DEVKITPPC_STRIP NAMES powerpc-eabi-strip HINTS "${DEVKITPPC}/bin")
if(NOT DEVKITPPC_STRIP)
   message(FATAL_ERROR "Could not find powerpc-eabi-strip")
endif()

set(CMAKE_ASM_COMPILER     "${DEVKITPPC_GCC}"   CACHE PATH "")
set(CMAKE_C_COMPILER       "${DEVKITPPC_GCC}"   CACHE PATH "")
set(CMAKE_CXX_COMPILER     "${DEVKITPPC_GPP}"   CACHE PATH "")
set(CMAKE_LINKER           "${DEVKITPPC_LD}"    CACHE PATH "")
set(CMAKE_AR               "${DEVKITPPC_AR}"    CACHE PATH "")
set(CMAKE_STRIP            "${DEVKITPPC_STRIP}" CACHE PATH "")

set(WUT_C_FLAGS            "-mcpu=750 -meabi -mhard-float -Wl,-q -D__WIIU__ -D__WUT__")
set(CMAKE_C_FLAGS          "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS        "${WUT_C_FLAGS}" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS "\"-L${WUT_ROOT}/lib/stubs\" -specs=${WUT_ROOT}/share/wut.specs" CACHE STRING "")

set(WUT_STANDARD_LIBRARIES "\"${WUT_ROOT}/lib/libwut.a\"")
set(CMAKE_C_STANDARD_LIBRARIES "${WUT_STANDARD_LIBRARIES}" CACHE STRING "")
set(CMAKE_CXX_STANDARD_LIBRARIES "${WUT_STANDARD_LIBRARIES}" CACHE STRING "")
set(CMAKE_ASM_STANDARD_LIBRARIES "${WUT_STANDARD_LIBRARIES}" CACHE STRING "")

#for some reason cmake (3.14.3) doesn't appreciate having \" here
set(WUT_STANDARD_INCLUDE_DIRECTORIES "${WUT_ROOT}/include")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${WUT_STANDARD_INCLUDE_DIRECTORIES}" CACHE STRING "")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${WUT_STANDARD_INCLUDE_DIRECTORIES}" CACHE STRING "")
set(CMAKE_ASM_STANDARD_INCLUDE_DIRECTORIES "${WUT_STANDARD_INCLUDE_DIRECTORIES}" CACHE STRING "")

# Find tools
find_program(ELF2RPL_BIN NAMES elf2rpl HINTS "${DEVKITPRO}/tools/bin")
if(NOT ELF2RPL_BIN)
   message(FATAL_ERROR "Could not find elf2rpl")
endif()

find_program(RPLEXPORTGEN_BIN NAMES rplexportgen HINTS "${DEVKITPRO}/tools/bin")
if(NOT RPLEXPORTGEN_BIN)
   message(FATAL_ERROR "Could not find rplexportgen")
endif()

# Tools
set(WUT_ELF2RPL "${ELF2RPL_BIN}" CACHE PATH "")
set(WUT_RPLEXPORTGEN "${RPLEXPORTGEN_BIN}" CACHE PATH "")

# Flags
set(WUT TRUE)
set(WIIU TRUE)

# There is no shared lib support in devkitPPC
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available")
