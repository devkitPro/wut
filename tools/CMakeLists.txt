project(tools)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(libraries)

include_directories(common)
add_subdirectory(elf2rpl)
add_subdirectory(readrpl)
add_subdirectory(rplimportgen)
add_subdirectory(rplexportgen)
add_subdirectory(udplogserver)
