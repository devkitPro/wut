cmake_minimum_required(VERSION 3.2)

macro(wut_enable_newlib target)
   set_property(TARGET ${target}
      APPEND_STRING PROPERTY
         LINK_FLAGS  " -Wl,--whole-archive -lwutnewlib -Wl,--no-whole-archive")
endmacro(wut_enable_newlib)

macro(wut_enable_devoptab target)
   set_property(TARGET ${target}
      APPEND_STRING PROPERTY
         LINK_FLAGS  " -Wl,--whole-archive -lwutdevoptab -Wl,--no-whole-archive")
endmacro(wut_enable_devoptab)

macro(wut_enable_stdcpp target)
   target_link_libraries(${target}
      stdc++)

   set_property(TARGET ${target}
      APPEND_STRING PROPERTY
         COMPILE_FLAGS "-std=c++17")

   set_property(TARGET ${target}
      APPEND_STRING PROPERTY
         LINK_FLAGS " -Wl,--whole-archive -lwutstdc++ -Wl,--no-whole-archive")
endmacro(wut_enable_stdcpp)

macro(wut_create_rpx target source)
   target_link_libraries(${source}
      wutcrt
      coreinit)

   add_custom_target(${target} ALL
      COMMAND ${WUT_ELF2RPL} ${source} ${target}
      DEPENDS ${source}
      COMMENT "Converting to RPX ${target}")

  add_dependencies(${target} ${source})
endmacro(wut_create_rpx)
