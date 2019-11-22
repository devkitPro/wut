cmake_minimum_required(VERSION 3.2)

# Links against wutnewlib
macro(wut_enable_newlib target)
   message(DEPRECATION "wut_enable_newlib is deprecated and has no effect - it is always enabled; and the macro will be removed in a future release. Please remove it from your CMakeLists.")
endmacro()

# Links against stdc++ wutstdc++ and set -std=c++17
macro(wut_enable_stdcpp target)
   message(DEPRECATION "wut_enable_stdcpp is deprecated and has no effect - it is always enabled when using C++; and the macro will be removed in a future release. Please remove it from your CMakeLists.")
endmacro()

# Links against devoptab
macro(wut_enable_devoptab target)
   message(DEPRECATION "wut_enable_devoptab is deprecated and has no effect - it is always enabled; and the macro will be removed in a future release. Please remove it from your CMakeLists.")
endmacro()

# Links against wutmalloc
macro(wut_default_malloc target)
   message(DEPRECATION "wut_default_malloc is deprecated and has no effect - it is always enabled; and the macro will be removed in a future release. Please remove it from your CMakeLists.")
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

function(wut_create_rpl_deprecated target source)
   set(RPL_OPTIONS IS_RPX)
   set(RPL_SINGLE_ARGS "")
   set(RPL_MULTI_ARGS "")
   cmake_parse_arguments(RPL "${RPL_OPTIONS}" "${RPL_SINGLE_ARGS}" "${RPL_MULTI_ARGS}" "${ARGN}")

   if(RPL_IS_RPX)
      # Do nothing - the defaults are good for RPX
   else()
      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --rpl)
      set_property(TARGET ${source} APPEND_STRING PROPERTY
         LINK_FLAGS "-specs=${WUT_ROOT}/share/rpl.specs")
   endif()

   add_custom_target(${target} ALL
      COMMAND ${CMAKE_STRIP} -g ${source}
      COMMAND ${WUT_ELF2RPL} ${ELF2RPL_FLAGS} ${source} ${target}
      DEPENDS ${source}
      COMMENT "Converting to RPX ${target}")

   add_dependencies(${target} ${source})
endfunction()

function(wut_create_rpl target)
   set(RPL_OPTIONS IS_RPX)
   set(RPL_SINGLE_ARGS "")
   set(RPL_MULTI_ARGS "")
   cmake_parse_arguments(RPL "${RPL_OPTIONS}" "${RPL_SINGLE_ARGS}" "${RPL_MULTI_ARGS}" "${ARGN}")

   if(${ARGC} GREATER 1 AND NOT "${ARGV1}" STREQUAL "IS_RPX")
      message(DEPRECATION "wut_create_rpl(dest.rpx source) is deprecated, prefer using wut_create_rpl(target)")
      wut_create_rpl_deprecated(${ARGV0} ${ARGV1} ${RPL_OPTIONS})
      return()
   endif()

   if(RPL_IS_RPX)
      # Do nothing - the defaults are good for RPX
   else()
      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --rpl)
      set_property(TARGET ${target} APPEND_STRING PROPERTY
         LINK_FLAGS "-specs=${WUT_ROOT}/share/rpl.specs")
   endif()

   add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_STRIP} -g $<TARGET_FILE:${target}>
      COMMAND ${WUT_ELF2RPL} ${ELF2RPL_FLAGS} $<TARGET_FILE:${target}> $<TARGET_FILE_DIR:${target}>/${target}.rpx
      COMMENT "Creating ${target}.rpx")
endfunction()

function(wut_create_rpx)
   wut_create_rpl(${ARGV} IS_RPX)
endfunction()
