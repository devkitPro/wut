project(rplgen)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(rplgen
   ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(rplgen
   zlib)

install(TARGETS rplgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
