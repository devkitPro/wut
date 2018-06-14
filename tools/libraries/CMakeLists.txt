# excmd
add_library(excmd INTERFACE)
target_include_directories(excmd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/excmd/src")

# fmt
add_subdirectory(fmt)

# zlib
find_package(ZLIB QUIET)

if(NOT ZLIB_FOUND)
   # Disable zlib install
   set(SKIP_INSTALL_ALL 1)
   add_subdirectory(zlib)

   target_include_directories(zlib INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}/zlib"
      "${CMAKE_CURRENT_BINARY_DIR}/zlib")

   install(FILES "${CMAKE_BINARY_DIR}/bin/zlib.dll"
           DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
else()
   add_library(zlib INTERFACE)
   target_link_libraries(zlib INTERFACE ${ZLIB_LIBRARIES})
   target_include_directories(zlib INTERFACE ${ZLIB_INCLUDE_DIR})
endif()
