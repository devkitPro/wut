cmake_minimum_required(VERSION 3.2)
project(helloworld C)

project(helloworld C)

add_executable(helloworld
   main.c)

wut_create_rpx(helloworld)
wut_create_wuhb(helloworld
   CONTENT
   NAME "Hello World!"
   SHORTNAME "Hello World!"
   AUTHOR "Built with devkitPPC & wut"
   ICON 
   TVSPLASH 
   DRCSPLASH
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld.wuhb"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
