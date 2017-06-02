project(udplogserver)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(udplogserver ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(udplogserver PROPERTIES FOLDER tools)

if (MSVC)
   target_link_libraries(udplogserver PRIVATE ws2_32)
endif()

install(TARGETS udplogserver RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
