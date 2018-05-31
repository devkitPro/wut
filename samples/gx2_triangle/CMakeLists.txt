cmake_minimum_required(VERSION 3.2)
project(gx2_triangle C)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(gx2_triangle
   main.c)

target_link_libraries(gx2_triangle
   whb
   gfd
   gx2
   proc_ui
   nsysnet
   sysapp)

wut_create_rpx(gx2_triangle.rpx gx2_triangle)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gx2_triangle.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
