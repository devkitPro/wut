project(readrpl)

add_executable(readrpl
   generate_exports_def.cpp
   generate_exports_def.h
   main.cpp
   print.cpp
   print.h
   readrpl.h
   verify.cpp
   verify.h)

target_link_libraries(readrpl
   excmd
   fmt
   zlib)

install(TARGETS readrpl RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
