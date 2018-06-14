project(rplexportgen)

add_executable(rplexportgen
   rplexportgen.cpp)

target_link_libraries(rplexportgen
   zlibstatic)

install(TARGETS rplexportgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
