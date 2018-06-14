project(rplimportgen)

add_executable(rplimportgen
   rplimportgen.cpp)

target_link_libraries(rplimportgen
   zlibstatic)

install(TARGETS rplimportgen RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
