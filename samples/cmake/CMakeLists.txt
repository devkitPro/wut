cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)
project(samples)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_subdirectory(curl)
add_subdirectory(custom_default_heap)
add_subdirectory(erreula)
add_subdirectory(gx2_triangle)
add_subdirectory(helloworld)
add_subdirectory(helloworld_cpp)
add_subdirectory(my_first_rpl)
add_subdirectory(swkbd)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/content/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/content")
