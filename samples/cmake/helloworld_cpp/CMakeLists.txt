cmake_minimum_required(VERSION 3.2)
project(helloworld_cpp CXX)

add_executable(helloworld_cpp
   main.cpp)

wut_create_rpx(helloworld_cpp)
wut_create_wuhb(helloworld_cpp
   CONTENT
   NAME "Hello World! (C++)"
   SHORTNAME "Hello World!"
   AUTHOR "Built with devkitPPC & wut"
   ICON 
   TVSPLASH 
   DRCSPLASH
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld_cpp.wuhb"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
