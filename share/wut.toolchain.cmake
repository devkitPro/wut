message(DEPRECATION
   "This toolchain file has been superseded by devkitPro CMake. "
   "devkitPro CMake for Wii U can be invoked with the following wrapper script:\n"
   ""
   "/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake"
)

include(/opt/devkitpro/cmake/WiiU.cmake)
