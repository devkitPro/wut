# excmd
add_library(excmd INTERFACE)
target_include_directories(excmd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/excmd/src")

# fmt
add_subdirectory(fmt)
