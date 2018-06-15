cmake_minimum_required(VERSION 3.2)

# Load up the in-tree toolchain
set(WUT_ROOT "{CMAKE_CURRENT_SOURCE_DIR}/.." CACHE STRING "")
set(ENV{WUT_ROOT} ${WUT_ROOT})
set(CMAKE_TOOLCHAIN_FILE $ENV{WUT_ROOT}/share/wut.toolchain.cmake)

project(libraries C)

add_subdirectory(libgfd)
add_subdirectory(libwhb)
add_subdirectory(nn_swkbd)
add_subdirectory(wutcrt)
add_subdirectory(wutdevoptab_sd)
add_subdirectory(wutmalloc)
add_subdirectory(wutnewlib)
add_subdirectory(wutstdc++)
