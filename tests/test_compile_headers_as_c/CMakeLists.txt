cmake_minimum_required(VERSION 3.2)
project(test_compile_headers_as_c C)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(test_compile_headers_as_c
   main.c)

wut_create_rpx(test_compile_headers_as_c.rpx test_compile_headers_as_c)
