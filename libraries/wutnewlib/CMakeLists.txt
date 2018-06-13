cmake_minimum_required(VERSION 3.2)
project(wutnewlib C)

add_library(wutnewlib
   wut_clock.c
   wut_gettod_r.c
   wut_lock.c
   wut_malloc.c
   wut_malloc_lock.c
   wut_nanosleep.c
   wut_newlib.c
   wut_sbrk.c)
target_include_directories(wutnewlib PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutnewlib
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
