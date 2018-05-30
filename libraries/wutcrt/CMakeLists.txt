cmake_minimum_required(VERSION 3.2)
project(wutcrt C ASM)

add_library(wutcrt
   crt0_rpx.s
   wut_crt.c)

add_library(wutcrtrpl
   crt0_rpl.s
   wut_crt.c)

target_include_directories(wutcrt PRIVATE "${WUT_ROOT}/include")
target_include_directories(wutcrtrpl PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutcrt wutcrtrpl
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
