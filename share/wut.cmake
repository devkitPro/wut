cmake_minimum_required(VERSION 3.2)

# Links against wutnewlib
macro(wut_enable_newlib target)
   get_property(ENABLED_NEWLIB TARGET ${target} PROPERTY WUT_ENABLE_NEWLIB)
   if(NOT DEFINED ENABLED_NEWLIB)
      target_link_libraries(${target}
         -Wl,--whole-archive wutnewlib -Wl,--no-whole-archive)

      set_target_properties(${target} PROPERTIES WUT_ENABLE_NEWLIB 1)
   endif()
endmacro()

# Links against stdc++ wutstdc++ and set -std=c++17
macro(wut_enable_stdcpp target)
   get_property(ENABLED_STDCPP TARGET ${target} PROPERTY WUT_ENABLE_STDCPP)
   if(NOT DEFINED ENABLED_STDCPP)
      wut_enable_newlib(${target})

      target_link_libraries(${target}
         stdc++
         -Wl,--whole-archive wutstdc++ -Wl,--no-whole-archive)

      set_property(TARGET ${target} APPEND_STRING PROPERTY
         COMPILE_FLAGS "-std=c++17")

      set_target_properties(${target} PROPERTIES WUT_ENABLE_STDCPP 1)
   endif()
endmacro()

# Links against devoptab_sd
macro(wut_enable_devoptab_sd target)
   get_property(ENABLED_DEVOPTAB_SD TARGET ${target} PROPERTY WUT_ENABLE_DEVOPTAB_SD)
   if(NOT DEFINED ENABLED_DEVOPTAB_SD)
      target_link_libraries(${target}
         -Wl,--whole-archive wutdevoptab_sd -Wl,--no-whole-archive)

      set_target_properties(${target} PROPERTIES WUT_ENABLE_DEVOPTAB_SD 1)
   endif()
endmacro()

# Links against wutmalloc
macro(wut_default_malloc target)
   get_property(ENABLED_DEFAULT_MALLOC TARGET ${target} PROPERTY WUT_DEFAULT_MALLOC)
   if(NOT DEFINED ENABLED_DEFAULT_MALLOC)
      target_link_libraries(${target}
         -Wl,--whole-archive wutmalloc -Wl,--no-whole-archive)

      set_target_properties(${target} PROPERTIES WUT_DEFAULT_MALLOC 1)
   endif()
endmacro()

# Generates ${target}_exports.s from an exports file and adds it to the build
macro(wut_add_exports target exports_file)
   set(RPL_EXPORTS_FILE ${exports_file})
   if(NOT IS_ABSOLUTE ${exports_file})
      set(RPL_EXPORTS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${exports_file}")
   endif()

   set(RPL_EXPORT_GEN_OUTPUT ${target}_exports.s)

   add_custom_command(
      OUTPUT ${RPL_EXPORT_GEN_OUTPUT}
      COMMAND ${WUT_RPLEXPORTGEN} ${RPL_EXPORTS_FILE} ${RPL_EXPORT_GEN_OUTPUT}
      DEPENDS ${RPL_EXPORTS_FILE})
   target_sources(${target} PRIVATE ${RPL_EXPORT_GEN_OUTPUT})

   set_source_files_properties(${RPL_EXPORT_GEN_OUTPUT} PROPERTIES LANGUAGE C)
endmacro()

function(wut_create_rpl target source)
   set(RPL_OPTIONS IS_RPX)
   set(RPL_SINGLE_ARGS "")
   set(RPL_MULTI_ARGS "")
   cmake_parse_arguments(RPL "${RPL_OPTIONS}" "${RPL_SINGLE_ARGS}" "${RPL_MULTI_ARGS}" "${ARGN}")

   if(RPL_IS_RPX)
      target_link_libraries(${source}
         coreinit
         wutcrt)
   else()
      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --rpl)
      target_link_libraries(${source}
         coreinit
         wutcrtrpl)
   endif()

   target_link_libraries(${source}
      coreinit)

   add_custom_target(${target} ALL
      COMMAND ${WUT_ELF2RPL} ${ELF2RPL_FLAGS} ${source} ${target}
      DEPENDS ${source}
      COMMENT "Converting to RPX ${target}")

   add_dependencies(${target} ${source})
endfunction()

function(wut_create_rpx)
   wut_create_rpl(${ARGV} IS_RPX)
endfunction()
