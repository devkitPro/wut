cmake_minimum_required(VERSION 3.2)
project(samples-gx2-triangle)

file(GLOB_RECURSE SOURCE_FILES src/*.c)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_rpx_lite(triangle ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(triangle
    whb
    coreinit
    defaultheap
    gx2
    gfd
    nsysnet
    proc_ui
    sysapp)
