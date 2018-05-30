cmake_minimum_required(VERSION 3.2)

macro(wut_enable_newlib target)
   set_property(TARGET ${target} APPEND_STRING PROPERTY
      LINK_FLAGS  " -Wl,--whole-archive -lwutnewlib -Wl,--no-whole-archive")
endmacro(wut_enable_newlib)

macro(wut_enable_devoptab target)
   set_property(TARGET ${target} APPEND_STRING PROPERTY
      LINK_FLAGS  " -Wl,--whole-archive -lwutdevoptab -Wl,--no-whole-archive")
endmacro(wut_enable_devoptab)

macro(wut_enable_stdcpp target)
   target_link_libraries(${target}
      stdc++)

   set_property(TARGET ${target} APPEND_STRING PROPERTY
      COMPILE_FLAGS "-std=c++17")

   set_property(TARGET ${target} APPEND_STRING PROPERTY
      LINK_FLAGS " -Wl,--whole-archive -lwutstdc++ -Wl,--no-whole-archive")
endmacro(wut_enable_stdcpp)

function(wut_create_rpl target source)
   set(RPL_OPTIONS IS_RPX)
   set(RPL_SINGLE_ARGS EXPORTS_FILE)
   set(RPL_MULTI_ARGS "")
   cmake_parse_arguments(RPL "${RPL_OPTIONS}" "${RPL_SINGLE_ARGS}" "${RPL_MULTI_ARGS}" "${ARGN}")

   if(NOT RPL_IS_RPX)
      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --rpl)
   endif()

   if(RPL_EXPORTS_FILE)
      if(NOT IS_ABSOLUTE ${RPL_EXPORTS_FILE})
         set(RPL_EXPORTS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${RPL_EXPORTS_FILE}")
      endif()

      set(ELF2RPL_FLAGS ${ELF2RPL_FLAGS} --exports ${RPL_EXPORTS_FILE})
   endif()

   target_link_libraries(${source}
      wutcrt
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
