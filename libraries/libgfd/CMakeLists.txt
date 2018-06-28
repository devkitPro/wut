cmake_minimum_required(VERSION 3.2)
project(libgfd)

add_library(gfd STATIC
   src/gfd.c
   include/gfd.h)

target_include_directories(gfd PRIVATE "../../include")
target_include_directories(gfd PUBLIC "include")

install(TARGETS gfd
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h*")
