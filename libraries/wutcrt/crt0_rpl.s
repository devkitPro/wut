.extern main
.extern exit
.extern __init_wut
.extern __fini_wut

.section .crt0, "ax", @progbits
.global __rpl_start
__rpl_start:
   stwu 1, -0x14(1)
   mflr 0
   stw 0, 0x18(1)
   stw 3, 0xC(1)
   stw 4, 0x10(1)
   cmpwi 3, 2
   beq unload

load:
   # Load
   bl __init_wut
   bl __eabi
   lwz 3, 0xC(1)
   lwz 4, 0x10(1)
   bl rpl_entry
   addi 1, 1, 0x14
   blr

unload:
   # Handle unload
   lwz 3, 0xC(1)
   lwz 4, 0x10(1)
   bl rpl_entry
   addi 1, 1, 0x14
   b exit

