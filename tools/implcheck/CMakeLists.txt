project(implcheck)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(implcheck ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(implcheck PROPERTIES FOLDER tools)

target_link_libraries(implcheck PRIVATE
    ${EXCMD_LINK}
    ${FMTLIB_LINK}
    ${ZLIB_LINK})

install(TARGETS implcheck RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
