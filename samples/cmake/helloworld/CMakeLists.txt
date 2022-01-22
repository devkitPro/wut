cmake_minimum_required(VERSION 3.2)
project(helloworld C)

add_executable(helloworld
   main.c)

wut_create_rpx(helloworld)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/helloworld.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
