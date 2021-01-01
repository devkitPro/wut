cmake_minimum_required(VERSION 3.2)

# Generates ${target}_exports.s from an exports file and adds it to the build
function(wut_add_exports target exports_file)
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

   set(RPL_IMPORT_GEN_OUTPUT ${target}_imports.s)
   set(RPL_IMPORT_GEN_LD ${target}_imports.ld)
   add_custom_command(
      OUTPUT ${RPL_IMPORT_GEN_OUTPUT} ${RPL_IMPORT_GEN_LD}
      COMMAND ${WUT_RPLIMPORTGEN} ${RPL_EXPORTS_FILE} ${RPL_IMPORT_GEN_OUTPUT} ${RPL_IMPORT_GEN_LD}
      DEPENDS ${RPL_EXPORTS_FILE})
   set_source_files_properties(${RPL_IMPORT_GEN_OUTPUT} PROPERTIES LANGUAGE C)
   add_library(${target}_imports STATIC ${RPL_IMPORT_GEN_OUTPUT})
   set_target_properties(${target}_imports PROPERTIES PREFIX "")
   get_filename_component(RPL_IMPORT_LINKER_SCRIPT ${target}_imports.ld REALPATH BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
   target_link_libraries(${target}_imports INTERFACE "-T${RPL_IMPORT_LINKER_SCRIPT}")
endfunction()

function(wut_link_rpl target source)
   target_link_libraries(${target} ${source}_imports)
endfunction()

function(wut_create_rpl target)
   set(RPL_OPTIONS IS_RPX)
   set(RPL_SINGLE_ARGS "")
   set(RPL_MULTI_ARGS "")
   cmake_parse_arguments(RPL "${RPL_OPTIONS}" "${RPL_SINGLE_ARGS}" "${RPL_MULTI_ARGS}" "${ARGN}")

   if(RPL_IS_RPX)
      # Do nothing - the defaults are good for RPX
      set(RPL_SUFFIX "rpx")
   else()
      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --rpl)
      set_property(TARGET ${target} APPEND_STRING PROPERTY
         LINK_FLAGS "-specs=${WUT_ROOT}/share/rpl.specs")
      set(RPL_SUFFIX "rpl")
   endif()

   add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_STRIP} -g $<TARGET_FILE:${target}>
      COMMAND ${WUT_ELF2RPL} ${ELF2RPL_FLAGS} $<TARGET_FILE:${target}> $<TARGET_FILE_DIR:${target}>/${target}.${RPL_SUFFIX}
      COMMENT "Creating ${target}.${RPL_SUFFIX}")
endfunction()

function(wut_create_rpx)
   wut_create_rpl(${ARGV} IS_RPX)
endfunction()
