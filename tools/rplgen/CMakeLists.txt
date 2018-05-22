add_executable(wut-rplgen rplgen.cpp)
target_include_directories(wut-rplgen PRIVATE
   ${ZLIB_INCLUDE_DIR})
target_link_libraries(wut-rplgen
   ${ZLIB_LIBRARIES})

install(TARGETS wut-rplgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
