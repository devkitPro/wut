project(readrpl)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(readrpl
   ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(readrpl PRIVATE
   ${ZLIB_INCLUDE_DIR})

target_link_libraries(readrpl
   excmd
   fmt
   ${ZLIB_LIBRARIES})

install(TARGETS readrpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
