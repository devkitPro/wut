cmake_minimum_required(VERSION 3.2)
project(helloworld)

add_rpx(helloworld src/main.c)
target_link_libraries(helloworld
    coreinit
    proc_ui
    sysapp)
