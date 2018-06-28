cmake_minimum_required(VERSION 3.2)
project(libwhb)

add_library(whb STATIC
   src/commandserver.c
   src/console.c
   src/crash.c
   src/file.c
   src/gfx.c
   src/gfx_heap.c
   src/gfx_heap.h
   src/gfx_shader.c
   src/gfx_texture.c
   src/libmanager.c
   src/log.c
   src/log_cafe.c
   src/log_udp.c
   src/proc.c
   src/sdcard.c
   include/whb/align.h
   include/whb/commandserver.h
   include/whb/crash.h
   include/whb/file.h
   include/whb/gfx.h
   include/whb/libmanager.h
   include/whb/log_cafe.h
   include/whb/log_console.h
   include/whb/log.h
   include/whb/log_udp.h
   include/whb/proc.h
   include/whb/sdcard.h)

target_include_directories(whb PRIVATE "../../include")
target_include_directories(whb PRIVATE "../libgfd/include")
target_include_directories(whb PUBLIC "include")

install(TARGETS whb
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h*")

