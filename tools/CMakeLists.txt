project(tools)

if(MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
elseif(APPLE)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

add_subdirectory(libraries)

include_directories(common)
add_subdirectory(elf2rpl)
add_subdirectory(readrpl)
add_subdirectory(rplgen)
add_subdirectory(udplogserver)
