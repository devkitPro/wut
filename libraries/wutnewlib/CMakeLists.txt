cmake_minimum_required(VERSION 3.2)
project(wutnewlib C)

add_library(wutnewlib
   sleep.c
   syscalls.c)
target_include_directories(wutnewlib PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutnewlib
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
