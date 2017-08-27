project(readrpl)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(readrpl ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(readrpl PROPERTIES FOLDER tools)

target_link_libraries(readrpl PRIVATE
    ${EXCMD_LINK}
    ${FMTLIB_LINK}
    ${ZLIB_LINK})

install(TARGETS readrpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
