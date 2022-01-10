cmake_minimum_required(VERSION 3.2)
project(erreula CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(erreula
   main.cpp)

wut_create_rpx(erreula)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/erreula.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
