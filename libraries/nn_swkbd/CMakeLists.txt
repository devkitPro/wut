cmake_minimum_required(VERSION 3.2)
project(nn_swkbd CXX)

add_library(nn_swkbd
   nn_swkbd.cpp)

target_include_directories(nn_swkbd
   PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${WUT_ROOT}/include")

install(TARGETS nn_swkbd
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
       DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
       FILES_MATCHING PATTERN "*.h*")
