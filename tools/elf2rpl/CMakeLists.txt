project(elf2rpl)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(elf2rpl
   ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(elf2rpl PRIVATE
   ${ZLIB_INCLUDE_DIR})

target_link_libraries(elf2rpl
   fmt
   ${ZLIB_LIBRARIES})

install(TARGETS elf2rpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
