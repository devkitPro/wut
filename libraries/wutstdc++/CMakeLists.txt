cmake_minimum_required(VERSION 3.2)
project(wutstdc++ CXX)

add_library(wutstdc++
   condition_variable.cc
   future.cc
   gthread.cc
   gthread_cond.cc
   gthread_keys.cc
   gthread_mutex.cc
   gthread_once.cc
   gthread_recursive_mutex.cc
   mutex.cc
   shared_ptr.cc
   thread.cc
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
