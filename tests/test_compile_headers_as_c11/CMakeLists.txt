cmake_minimum_required(VERSION 3.2)
project(test_compile_headers_as_c11 C)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(test_compile_headers_as_c11
   main.c)

target_compile_options(test_compile_headers_as_c11 PRIVATE
   -Wall
   -Wextra
   -pedantic
   -Werror)

wut_create_rpx(test_compile_headers_as_c11)
