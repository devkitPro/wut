.extern main
.extern exit
.extern __init_wut
.extern __fini_wut

.global _start
_start:
   stwu 1, -0x8(1)
   stw 3, 0(1)
   stw 4, 4(1)
   cmpwi 3, 2
   beq unload

load:
   # Load
   bl __init_wut
   bl __eabi
   lwz 3, 0(1)
   lwz 4, 4(1)
   bl rpl_main
   addi 1, 1, 0x8
   blr

unload:
   # Handle unload
   lwz 3, 0(1)
   lwz 4, 4(1)
   bl rpl_main
   bl __fini_wut
   addi 1, 1, 0x8
   b exit
