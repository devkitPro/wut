cmake_minimum_required(VERSION 3.2)
project(test_compile_headers_as_cpp CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(test_compile_headers_as_cpp
   main.cpp)

wut_create_rpx(test_compile_headers_as_cpp.rpx test_compile_headers_as_cpp)
