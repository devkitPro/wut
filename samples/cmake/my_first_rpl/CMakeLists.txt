cmake_minimum_required(VERSION 3.2)
project(my_first_rpl C)

add_executable(my_first_rpl my_first_rpl.c)
wut_add_exports(my_first_rpl exports.def)
wut_create_rpl(my_first_rpl)

add_executable(my_first_rpx my_first_rpx.c)
wut_link_rpl(my_first_rpx my_first_rpl)
wut_create_rpx(my_first_rpx)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/my_first_rpx.rpx"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/my_first_rpl.rpl"
        DESTINATION "${CMAKE_INSTALL_PREFIX}")
