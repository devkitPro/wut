project(libraries)
include(ExternalProject)

# cppformat
set(CPPFORMAT_DIR "cppformat")
externalproject_add(cppformat
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${CPPFORMAT_DIR}"
    CMAKE_CACHE_ARGS
        -DCMAKE_C_COMPILER:string=${CMAKE_C_COMPILER}
        -DCMAKE_C_FLAGS:string=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_COMPILER:string=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS:string=${CMAKE_CXX_FLAGS}
        -DFMT_DOC:string=off
        -DFMT_INSTALL:string=off
        -DFMT_TEST:string=off
    INSTALL_COMMAND "")
externalproject_get_property(cppformat BINARY_DIR)
set_target_properties(cppformat PROPERTIES FOLDER libraries)

if(MSVC)
    set(CPPFORMAT_IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG "${BINARY_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}cppformat${CMAKE_FIND_LIBRARY_SUFFIXES}"
        IMPORTED_LOCATION_RELEASE "${BINARY_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}cppformat${CMAKE_FIND_LIBRARY_SUFFIXES}"
        IMPORTED_LOCATION_RELWITHDEBINFO "${BINARY_DIR}/RelWithDebInfo/${CMAKE_FIND_LIBRARY_PREFIXES}cppformat${CMAKE_FIND_LIBRARY_SUFFIXES}"
        IMPORTED_LOCATION_MINSIZEREL "${BINARY_DIR}/MinSizeRel/${CMAKE_FIND_LIBRARY_PREFIXES}cppformat${CMAKE_FIND_LIBRARY_SUFFIXES}")
else()
    set(CPPFORMAT_IMPORTED_LOCATION
        IMPORTED_LOCATION "${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}cppformat.a")
endif()

add_library(cppformat_import STATIC IMPORTED GLOBAL)
add_dependencies(cppformat_import cppformat)
set_target_properties(cppformat_import PROPERTIES ${CPPFORMAT_IMPORTED_LOCATION})

add_library(cppformat_final INTERFACE)
target_include_directories(cppformat_final INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/${CPPFORMAT_DIR}")
target_link_libraries(cppformat_final INTERFACE cppformat_import)
set(CPPFORMAT_LINK cppformat_final PARENT_SCOPE)

# excmd
set(EXCMD_DIR "excmd")
add_library(excmd INTERFACE)
target_include_directories(excmd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/${EXCMD_DIR}/src")
set(EXCMD_LINK excmd PARENT_SCOPE)

# zlib
find_package(ZLIB QUIET)

if(NOT ZLIB_FOUND)
    set(ZLIB_DIR "zlib")
    externalproject_add(zlib
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ZLIB_DIR}"
        PATCH_COMMAND ${CMAKE_COMMAND} -E remove <SOURCE_DIR>/zconf.h
        CMAKE_CACHE_ARGS
            -DCMAKE_C_COMPILER:string=${CMAKE_C_COMPILER}
            -DCMAKE_C_FLAGS:string=${CMAKE_C_FLAGS}
            -DCMAKE_CXX_COMPILER:string=${CMAKE_CXX_COMPILER}
            -DCMAKE_CXX_FLAGS:string=${CMAKE_CXX_FLAGS}
            -DBUILD_SHARED_LIBS:string=off
        INSTALL_COMMAND ""
        )
    externalproject_get_property(zlib BINARY_DIR)
    externalproject_add_step(zlib
        copy_to_binary
        DEPENDEES build
        DEPENDERS install
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${BINARY_DIR}/$(Configuration)" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)")
    set_target_properties(zlib PROPERTIES FOLDER libraries)

    if(MSVC)
        set(ZLIB_IMPORTED_LOCATION
            IMPORTED_LOCATION_DEBUG "${BINARY_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}zlibdstatic${CMAKE_FIND_LIBRARY_SUFFIXES}"
            IMPORTED_LOCATION_RELEASE "${BINARY_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}zlibstatic${CMAKE_FIND_LIBRARY_SUFFIXES}"
            IMPORTED_LOCATION_RELWITHDEBINFO "${BINARY_DIR}/RelWithDebInfo/${CMAKE_FIND_LIBRARY_PREFIXES}zlibstatic${CMAKE_FIND_LIBRARY_SUFFIXES}"
            IMPORTED_LOCATION_MINSIZEREL "${BINARY_DIR}/MinSizeRel/${CMAKE_FIND_LIBRARY_PREFIXES}zlibstatic${CMAKE_FIND_LIBRARY_SUFFIXES}")
    else()
        set(ZLIB_IMPORTED_LOCATION
            IMPORTED_LOCATION "${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}z.a")
    endif()

    add_library(zlib_import STATIC IMPORTED GLOBAL)
    add_dependencies(zlib_import zlib)
    set_target_properties(zlib_import PROPERTIES ${ZLIB_IMPORTED_LOCATION})

    set(ZLIB_LIBRARIES zlib_import)
    set(ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/${ZLIB_DIR} ${BINARY_DIR})
endif()

add_library(zlib_final INTERFACE)
target_include_directories(zlib_final INTERFACE ${ZLIB_INCLUDE_DIRS})
target_link_libraries(zlib_final INTERFACE ${ZLIB_LIBRARIES})
set(ZLIB_LINK zlib_final PARENT_SCOPE)
