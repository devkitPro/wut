cmake_minimum_required(VERSION 3.2)
project(swkbd CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(swkbd
   main.cpp)

target_link_libraries(swkbd
   whb
   gx2
   coreinit
   proc_ui
   sysapp
   nsysnet
   nn_ac
   nn_swkbd
   vpad)

wut_enable_newlib(swkbd)
wut_enable_stdcpp(swkbd)

wut_create_rpx(swkbd_sample.rpx
               swkbd)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swkbd_sample.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
