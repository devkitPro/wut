cmake_minimum_required(VERSION 3.10)
project(swkbd CXX)

add_executable(swkbd
   main.cpp)

wut_create_rpx(swkbd)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swkbd.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
