cmake_minimum_required(VERSION 3.2)
project(erreula CXX)

add_executable(erreula
   main.cpp)

wut_create_rpx(erreula)
wut_create_wuhb(erreula
   CONTENT
   NAME "Error Viewer"
   SHORTNAME "Error Viewer"
   AUTHOR "Built with devkitPPC & wut"
   ICON 
   TVSPLASH 
   DRCSPLASH
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/erreula.wuhb"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
