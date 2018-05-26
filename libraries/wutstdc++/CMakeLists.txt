cmake_minimum_required(VERSION 3.2)
project(wutstdc++ CXX)

add_library(wutstdc++
   wut_gthread.cc
   wut_gthread_cond.cc
   wut_gthread_keys.cc
   wut_gthread_mutex.cc
   wut_gthread_once.cc
   wut_gthread_recursive_mutex.cc
   wut_gthread_thread.cc)

target_compile_definitions(wutstdc++
   PRIVATE _GLIBCXX_HAS_GTHREADS)

target_include_directories(wutstdc++
   PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${WUT_ROOT}/include")

install(TARGETS wutstdc++
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
       DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
       FILES_MATCHING PATTERN "*.h*")
