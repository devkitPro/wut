project(rplgen)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(rplgen
   ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(rplgen PRIVATE
   ${ZLIB_INCLUDE_DIR})

target_link_libraries(rplgen
   ${ZLIB_LIBRARIES})

install(TARGETS rplgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
