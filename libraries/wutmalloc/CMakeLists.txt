cmake_minimum_required(VERSION 3.2)
project(wutmalloc C)

add_library(wutmalloc
   wut_malloc.c)
target_include_directories(wutmalloc PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutmalloc
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
