project(udplogserver)

add_executable(udplogserver
   main.cpp)

if(MSVC)
   target_link_libraries(udplogserver PRIVATE ws2_32)
endif()

install(TARGETS udplogserver RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
