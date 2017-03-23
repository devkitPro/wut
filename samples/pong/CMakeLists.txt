cmake_minimum_required(VERSION 3.2)
project(pong)

include($ENV{WUT_ROOT}/cmake/wut-toolchain.cmake)

file(GLOB_RECURSE SOURCE_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_rpx(pong ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(pong
    coreinit
    proc_ui
    vpad)
