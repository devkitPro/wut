cmake_minimum_required(VERSION 3.2)
project(helloworld C)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(helloworld
   main.c)

target_link_libraries(helloworld
   whb
   coreinit
   proc_ui
   sysapp)

wut_create_rpx(helloworld.rpx helloworld)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
