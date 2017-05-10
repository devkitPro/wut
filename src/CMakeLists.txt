externalproject_add(crt
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/crt"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

externalproject_add(crt-lite
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/crt-lite"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

externalproject_add(rpl
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/rpl"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

externalproject_add(libdefaultheap
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/libdefaultheap"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

externalproject_add(libgfd
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/libgfd"
   CMAKE_GENERATOR "Unix Makefiles"
   INSTALL_DIR "${CMAKE_BINARY_DIR}/staging"
   CMAKE_CACHE_ARGS
      -DDEVKITPPC:string=${DEVKITPPC}
      -DWUT_ROOT:string=${CMAKE_SOURCE_DIR}
      -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE:string=${CMAKE_SOURCE_DIR}/cmake/wut-toolchain.cmake)

# We must force build because changes are not detected with ExternalProject...
externalproject_add_step(crt forcebuild
   COMMAND ${CMAKE_COMMAND} -E echo "Force build of crt"
   DEPENDEES  "configure"
   DEPENDERS "build"
   ALWAYS 1)

externalproject_add_step(crt-lite forcebuild
   COMMAND ${CMAKE_COMMAND} -E echo "Force build of crt-lite"
   DEPENDEES  "configure"
   DEPENDERS "build"
   ALWAYS 1)

externalproject_add_step(rpl forcebuild
   COMMAND ${CMAKE_COMMAND} -E echo "Force build of rpl"
   DEPENDEES  "configure"
   DEPENDERS "build"
   ALWAYS 1)

externalproject_add_step(libdefaultheap forcebuild
   COMMAND ${CMAKE_COMMAND} -E echo "Force build of libdefaultheap"
   DEPENDEES  "configure"
   DEPENDERS "build"
   ALWAYS 1)

externalproject_add_step(libgfd forcebuild
   COMMAND ${CMAKE_COMMAND} -E echo "Force build of libgfd"
   DEPENDEES  "configure"
   DEPENDERS "build"
   ALWAYS 1)
