.extern main
.extern exit
.extern __init_wut
.extern __fini_wut

.global _start
_start:
   stwu 1, -0x8(1)
   stw 3, 0(1)
   stw 4, 4(1)
   bl __init_wut
   lwz 3, 0(1)
   lwz 4, 4(1)
   bl main
   bl __fini_wut
   # Calling __fini is leading to crashes!
   # bl __fini
   addi 1, 1, 0x8
   b exit
