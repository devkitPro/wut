cmake_minimum_required(VERSION 3.2)
project(libgfd)

file(GLOB_RECURSE SOURCE_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(gfd STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(gfd PRIVATE "../../include")
target_include_directories(gfd PUBLIC "include")

install(TARGETS gfd
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h*")
