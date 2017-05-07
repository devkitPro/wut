cmake_minimum_required(VERSION 3.2)
project(libgfd)

add_library(gfd src/libgfd.c)
target_include_directories(gfd PRIVATE "../../include")
target_include_directories(gfd PUBLIC "include")
install(TARGETS gfd ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
