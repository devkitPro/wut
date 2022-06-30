.extern main
.extern exit
.extern __init_wut
.extern __fini_wut
.extern __preinit_user

.section .crt0, "ax", @progbits
.global __rpx_start
__rpx_start:
   stwu 1, -0x14(1)
   mflr 0
   stw 0, 0x18(1)
   stw 3, 0xC(1)
   stw 4, 0x10(1)
   bl __init_wut
   lwz 3, 0xC(1)
   lwz 4, 0x10(1)
   bl main
   addi 1, 1, 0x14
   b exit

# -----------------------------------
# export for __preinit_user
# -----------------------------------
.section .fexports, "ax", @0x80000001
.align 4

.long 1
.long 0xa7fef0c2

.long __preinit_user
.long 0x10

.string "__preinit_user"
