cmake_minimum_required(VERSION 3.2)
project(gx2_triangle C)

add_executable(gx2_triangle
   main.c)

wut_create_rpx(gx2_triangle)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gx2_triangle.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
