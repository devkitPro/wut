cmake_minimum_required(VERSION 3.2)
project(swkbd CXX)

add_executable(swkbd
   main.cpp)

wut_create_rpx(swkbd)
wut_create_wuhb(swkbd
   CONTENT
   NAME "Software Keyboard"
   SHORTNAME "Software Keyboard"
   AUTHOR "Built with devkitPPC & wut"
   ICON 
   TVSPLASH 
   DRCSPLASH
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swkbd.wuhb"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
