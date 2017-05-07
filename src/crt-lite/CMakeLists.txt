cmake_minimum_required(VERSION 3.2)
project(wut-crt-lite)

set_property(SOURCE crt0.S PROPERTY LANGUAGE C)

add_library(crt-lite
    crt0.S)
set_target_properties(crt-lite PROPERTIES
    COMPILE_FLAGS "-fno-builtin -ffreestanding"
    LINKER_FLAGS "-fPIC")
target_include_directories(crt-lite PRIVATE "../../include")

install(TARGETS crt-lite ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
