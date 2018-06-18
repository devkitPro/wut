cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE $ENV{WUT_ROOT}/share/wut.toolchain.cmake)
project(tests)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_subdirectory(test_compile_headers_as_c)
add_subdirectory(test_compile_headers_as_cpp)
