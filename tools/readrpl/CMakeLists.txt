project(readrpl)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(readrpl
   ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(readrpl
   excmd
   fmt
   zlib)

install(TARGETS readrpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
