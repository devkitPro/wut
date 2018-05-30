cmake_minimum_required(VERSION 3.2)
project(helloworld_std_thread CXX)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(helloworld_std_thread
   main.cpp)

target_link_libraries(helloworld_std_thread
   whb
   coreinit
   proc_ui
   sysapp)

wut_enable_newlib(helloworld_std_thread)
wut_enable_stdcpp(helloworld_std_thread)

wut_create_rpx(helloworld_std_thread.rpx
               helloworld_std_thread)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld_std_thread.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
