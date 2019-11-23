cmake_minimum_required(VERSION 3.2)
project(helloworld_cpp CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(helloworld_cpp
   main.cpp)

wut_create_rpx(helloworld_cpp)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld_cpp.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
