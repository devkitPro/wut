cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE $ENV{WUT_ROOT}/share/wut.toolchain.cmake)
project(tests)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

include_directories("test_compile_headers_common")
add_subdirectory(test_compile_headers_as_c11)
add_subdirectory(test_compile_headers_as_c99)
add_subdirectory(test_compile_headers_as_cpp)
