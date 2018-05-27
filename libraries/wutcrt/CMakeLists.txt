cmake_minimum_required(VERSION 3.2)
project(wutnewlib C)

set_property(SOURCE crt0.s PROPERTY LANGUAGE C)

add_library(wutcrt
   crt0.s
   wut_crt.c)
target_include_directories(wutcrt PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutcrt
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
