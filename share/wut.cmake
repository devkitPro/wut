cmake_minimum_required(VERSION 3.2)

macro(wut_enable_stdcpp target)
   target_link_libraries(${target}
       wutnewlib
       stdc++)

   set_target_properties(${target} PROPERTIES
      COMPILE_FLAGS "-std=c++17"
      LINK_FLAGS "-Wl,--whole-archive -lwutstdc++ -Wl,--no-whole-archive")
endmacro(wut_enable_stdcpp)

macro(wut_create_rpx target source)
   target_link_libraries(${source}
       wutnewlib
       coreinit)

   add_custom_target(${target} ALL
       COMMAND ${WUT_ELF2RPL} ${source} ${target}
       DEPENDS ${source}
       COMMENT "Converting to RPX ${target}")

  add_dependencies(${target} ${source})
endmacro(wut_create_rpx)
