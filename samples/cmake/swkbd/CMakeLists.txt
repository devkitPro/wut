cmake_minimum_required(VERSION 3.2)
project(swkbd CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(swkbd
   main.cpp)

wut_create_rpx(swkbd_sample.rpx swkbd)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swkbd_sample.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
