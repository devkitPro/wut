cmake_minimum_required(VERSION 3.2)
project(curl C)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(curl
   main.c)

target_link_libraries(curl
   whb
   proc_ui
   sysapp
   nsysnet
   nlibcurl)

wut_create_rpx(curl)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/curl.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
