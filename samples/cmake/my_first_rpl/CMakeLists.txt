cmake_minimum_required(VERSION 3.2)
project(my_first_rpl C)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(my_first_rpl
   my_first_rpl.c)

wut_add_exports(my_first_rpl
   exports.def)

wut_create_rpl(my_first_rpl.rpl
               my_first_rpl)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/my_first_rpl.rpl"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
