project(rplexportgen)

add_executable(rplexportgen
   rplexportgen.cpp)

target_link_libraries(rplexportgen
   zlib)

install(TARGETS rplexportgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
