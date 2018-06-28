project(elf2rpl)

add_executable(elf2rpl
   main.cpp)

target_link_libraries(elf2rpl
   excmd
   fmt
   zlibstatic)

install(TARGETS elf2rpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
