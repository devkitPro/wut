# excmd
add_library(excmd INTERFACE)
target_include_directories(excmd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/excmd/src")

# fmt
add_subdirectory(fmt)

# zlib
find_package(ZLIB QUIET)

if(NOT ZLIB_FOUND)
   add_subdirectory(zlib)

   target_include_directories(zlib INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}/zlib"
      "${CMAKE_CURRENT_BINARY_DIR}/zlib")
else()
   add_library(zlib INTERFACE)
   target_link_libraries(zlib INTERFACE ${ZLIB_LIBRARIES})
   target_include_directories(zlib INTERFACE ${ZLIB_INCLUDE_DIR})
endif()
