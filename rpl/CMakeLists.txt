cmake_minimum_required(VERSION 3.2)
project(wut-libraries)

include(../cmake/wut-toolchain.cmake)

set_property(SOURCE common/stub.S PROPERTY LANGUAGE C)

set(WUT_RPL_COMPILE_FLAGS "-Wno-unused-variable -fno-builtin -ffreestanding")
set(WUT_RPL_LINKER_FLAGS "-nostdlib -nostartfiles")

macro(add_wut_rpl target)
    add_library(${target}
        common/lib.c
        common/stub.S
        ${target}/config.h
        ${target}/exports.h)
    target_include_directories(${target} PRIVATE "common" "${target}")
    set_target_properties(${target} PROPERTIES
        COMPILE_FLAGS "${WUT_RPL_COMPILE_FLAGS}"
        LINK_FLAGS "${WUT_RPL_LINKER_FLAGS}")
    install(TARGETS ${target} ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endmacro()

add_wut_rpl(coreinit)
add_wut_rpl(gx2)
add_wut_rpl(nsysnet)
add_wut_rpl(nn_ac)
add_wut_rpl(proc_ui)
add_wut_rpl(sndcore2)
add_wut_rpl(sysapp)
add_wut_rpl(vpad)
