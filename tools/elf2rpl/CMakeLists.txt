project(elf2rpl)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(elf2rpl ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(elf2rpl PROPERTIES FOLDER tools)

target_link_libraries(elf2rpl PRIVATE
    ${ZLIB_LINK})

install(TARGETS elf2rpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
