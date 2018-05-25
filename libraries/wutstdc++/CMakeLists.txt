cmake_minimum_required(VERSION 3.2)
project(wutstdc++ CXX)

add_library(wutstdc++
   thread.cc
   gthread_keys.cc
   include/bits/gthr-default.h)

target_compile_definitions(wutstdc++
   PRIVATE _GLIBCXX_HAS_GTHREADS)

target_include_directories(wutstdc++
   PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${WUT_ROOT}/include")

install(TARGETS wutstdc++
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
       DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
       FILES_MATCHING PATTERN "*.h*")
