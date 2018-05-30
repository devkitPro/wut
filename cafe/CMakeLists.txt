cmake_minimum_required(VERSION 3.2)
project(cafe C CXX)
enable_language(ASM)

macro(add_cafe_library target)
   add_custom_command(
      OUTPUT ${target}.s
      COMMAND ${WUT_RPLIMPORTGEN} ${CMAKE_CURRENT_SOURCE_DIR}/${target}/exports.def ${target}.s
      DEPENDS ${target}/exports.def)

   add_library(${target} STATIC ${target}.s)
   install(TARGETS ${target} ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endmacro()

add_cafe_library(coreinit)
add_cafe_library(gx2)
add_cafe_library(nn_ac)
add_cafe_library(nsysnet)
add_cafe_library(proc_ui)
add_cafe_library(sndcore2)
add_cafe_library(sysapp)
add_cafe_library(vpad)
