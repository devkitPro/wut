cmake_minimum_required(VERSION 3.2)
project(samples)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_subdirectory(custom_default_heap)
add_subdirectory(helloworld)
add_subdirectory(helloworld_std_thread)
add_subdirectory(gx2_triangle)
add_subdirectory(my_first_rpl)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/content/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/content")
