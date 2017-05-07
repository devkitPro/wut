cmake_minimum_required(VERSION 3.2)
project(wut-tools)

set(CMAKE_CXX_STANDARD 14)
include_directories("common")

add_subdirectory(elf2rpl)
add_subdirectory(readrpl)
add_subdirectory(implcheck)
