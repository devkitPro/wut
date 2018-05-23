cmake_minimum_required(VERSION 3.2)
project(libdefaultheap)

file(GLOB_RECURSE SOURCE_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(defaultheap STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(defaultheap PRIVATE "../../include")
target_include_directories(defaultheap PUBLIC "include")

install(TARGETS defaultheap
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h*")
