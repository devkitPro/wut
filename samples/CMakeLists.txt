cmake_minimum_required(VERSION 3.2)
project(samples)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_subdirectory(helloworld)
add_subdirectory(helloworld_std_thread)
