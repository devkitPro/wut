cmake_minimum_required(VERSION 3.2)

macro(wut_create_rpx target source)
  add_custom_target(${target} ALL
    COMMAND ${WUT_ELF2RPL} ${source} ${target}
    DEPENDS ${source}
    COMMENT "Converting to RPX ${target}"
  )
  add_dependencies(${target} ${source})
endmacro(wut_create_rpx)
