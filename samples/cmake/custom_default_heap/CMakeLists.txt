cmake_minimum_required(VERSION 3.2)
project(custom_default_heap C)

add_executable(custom_default_heap
   main.c)

wut_add_exports(custom_default_heap exports.def)
wut_create_rpx(custom_default_heap)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/custom_default_heap.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
