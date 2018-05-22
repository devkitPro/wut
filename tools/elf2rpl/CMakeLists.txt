add_executable(wut-elf2rpl main.cpp)
target_include_directories(wut-elf2rpl PRIVATE
   ${ZLIB_INCLUDE_DIR})
target_link_libraries(wut-elf2rpl
   fmt
   ${ZLIB_LIBRARIES})

install(TARGETS wut-elf2rpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
