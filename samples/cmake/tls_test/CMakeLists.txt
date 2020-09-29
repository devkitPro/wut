cmake_minimum_required(VERSION 3.2)
project(tls_test CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(tls_test
   main.cpp)

wut_create_rpx(tls_test)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/tls_test.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
