cmake_minimum_required(VERSION 3.2)
project(libwhb)

file(GLOB_RECURSE SOURCE_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(whb STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(whb PRIVATE "../../include")
target_include_directories(whb PRIVATE "../libdefaultheap/include")
target_include_directories(whb PRIVATE "../libgfd/include")
target_include_directories(whb PUBLIC "include")

install(TARGETS whb
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h*")

