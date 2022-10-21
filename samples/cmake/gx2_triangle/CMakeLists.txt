cmake_minimum_required(VERSION 3.2)
project(gx2_triangle C)

add_executable(gx2_triangle
   main.c)

wut_create_rpx(gx2_triangle)
wut_create_wuhb(gx2_triangle
   CONTENT "content/shaders/"
   NAME "GX2 Triangle"
   SHORTNAME "GX2 Triangle"
   AUTHOR "Built with devkitPPC & wut"
   ICON 
   TVSPLASH 
   DRCSPLASH
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gx2_triangle.wuhb"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
