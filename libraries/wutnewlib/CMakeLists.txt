cmake_minimum_required(VERSION 3.2)
project(wutnewlib C)

set_property(SOURCE crt0.s PROPERTY LANGUAGE C)

add_library(wutnewlib
   crt0.s
   syscalls.c)
target_include_directories(wutnewlib PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutnewlib
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
