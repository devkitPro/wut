cmake_minimum_required(VERSION 3.2)
project(test_compile_headers_as_c99 C)

set(CMAKE_C_STANDARD 99)

add_executable(test_compile_headers_as_c99
   main.c)

target_compile_options(test_compile_headers_as_c99 PRIVATE
   -Wall
   -Wextra
   -pedantic
   -Werror)

wut_create_rpx(test_compile_headers_as_c99)
