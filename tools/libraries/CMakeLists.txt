include(CheckTypeSize)

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
   set(BUILD_SHARED_LIBS OFF)
   add_subdirectory(zlib)

   # Fix zlib tool / example includes
   target_include_directories(example PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/zlib")
   target_include_directories(minigzip PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

   check_type_size(off64_t OFF64_T)
   if(HAVE_OFF64_T)
      target_include_directories(example64 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/zlib")
      target_include_directories(minigzip64 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/zlib")
   endif()

   target_include_directories(zlibstatic INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}/zlib"
      "${CMAKE_CURRENT_BINARY_DIR}/zlib")
else()
   # Not actually static, but who cares...
   add_library(zlibstatic INTERFACE)
   target_link_libraries(zlibstatic INTERFACE ${ZLIB_LIBRARIES})
   target_include_directories(zlibstatic INTERFACE ${ZLIB_INCLUDE_DIR})
endif()
