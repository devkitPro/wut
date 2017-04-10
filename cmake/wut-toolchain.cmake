set(DEVKITPPC $ENV{DEVKITPPC} CACHE STRING "Path to devkitPPC install")
set(WUT_ROOT $ENV{WUT_ROOT} CACHE STRING "Path to wut install")

# Check for DEVKITPPC
if(NOT DEVKITPPC)
    message(FATAL_ERROR "You must have defined DEVKITPPC before calling cmake.")
endif()

if(NOT WUT_ROOT)
    # Let's try find it!
    if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake")
        # ./ for wut/CMakeLists.txt
        set(FIND_WUT_ROOT ${CMAKE_SOURCE_DIR})
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/../cmake/wut-toolchain.cmake")
        # ../ for wut/rpl/CMakeLists.txt
        set(FIND_WUT_ROOT "${CMAKE_SOURCE_DIR}/..")
    elseif(EXISTS "${CMAKE_TOOLCHAIN_FILE}")
        # We're a toolchain file installed in WUT_ROOT/cmake
        set(FIND_WUT_ROOT "${CMAKE_TOOLCHAIN_FILE}/..")
    endif()
endif()

if(NOT WUT_ROOT)
    message(FATAL_ERROR "You must have defined WUT_ROOT before calling cmake.")
endif()

# Set it in ENV to make sure it gets passed around, cmake is a bit odd like that.
set(ENV{WUT_ROOT} ${WUT_ROOT})
set(ENV{DEVKITPPC} ${DEVKITPPC})

set(CMAKE_SYSTEM_NAME Generic)

if(WIN32)
    # Because "Unix Makefiles" generator does not set this, even if on Windows
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
endif()

set(CMAKE_C_COMPILER "${DEVKITPPC}/bin/powerpc-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX}")
set(CMAKE_CXX_COMPILER "${DEVKITPPC}/bin/powerpc-eabi-g++${CMAKE_EXECUTABLE_SUFFIX}")

set(CMAKE_FIND_ROOT_PATH ${DEVKITPPC})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(DEVKIT_COMPILE_FLAGS "-mcpu=750 -meabi -mhard-float -msdata")
set(DEVKIT_LINKER_FLAGS "-nostartfiles -L${DEVKITPPC}/lib")

set(RPX_COMPILE_FLAGS "\
    ${DEVKIT_COMPILE_FLAGS}")

set(RPX_LINKER_FLAGS "\
    ${DEVKIT_LINKER_FLAGS} \
    -pie -fPIE -z common-page-size=64 -z max-page-size=64 -T ${WUT_ROOT}/rules/rpl.ld -L${WUT_ROOT}/lib\
    -Wl,-wrap,__eabi")

set(ELF_TO_RPL ${WUT_ROOT}/bin/elf2rpl${CMAKE_EXECUTABLE_SUFFIX})

macro(add_rpx target)
    add_executable(${ARGV})
    set_target_properties(${target} PROPERTIES
        COMPILE_FLAGS "${RPX_COMPILE_FLAGS}"
        LINK_FLAGS "${RPX_LINKER_FLAGS}")

    target_include_directories(${target} PRIVATE "${WUT_ROOT}/include")
    target_link_libraries(${target} crt)

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${ELF_TO_RPL}" "$<TARGET_FILE:${target}>" "$<TARGET_FILE:${target}>.rpx"
        COMMENT "Converting $<TARGET_FILE:${target}> to rpx")
endmacro()
