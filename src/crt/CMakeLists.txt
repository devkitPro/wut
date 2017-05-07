cmake_minimum_required(VERSION 3.2)
project(wut-crt)

set_property(SOURCE crt0.S PROPERTY LANGUAGE C)

add_library(crt
    crt0.S
    fs_dev.c
    newlib.c)
set_target_properties(crt PROPERTIES
    COMPILE_FLAGS "-fno-builtin -ffreestanding"
    LINKER_FLAGS "-fPIC")
target_include_directories(crt PRIVATE "../../include")

install(TARGETS crt ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
