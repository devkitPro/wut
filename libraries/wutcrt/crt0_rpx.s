.extern main
.extern exit
.extern __init_wut
.extern __fini_wut
.extern __preinit_user
.extern OSIsDebuggerInitialized

.section .crt0, "ax", @progbits
.global __rpx_start
__rpx_start:
   stwu 1, -0x10(1)
   mflr 0
   stw 0, 0x14(1)
   stw 3, 0x8(1)
   stw 4, 0xC(1)
   bl OSIsDebuggerInitialized
   cmpwi 3,0x0
   beq init_wut
   li 3, 2                  # DBGCTL_INIT_BREAKPOINT
   lis 4, main@h            # Used for the initial bp if (((appFlags & 0x40) != 0) || ((appFlags & 0x10) != 0))
   ori 4,4, main@l
   lis 5, __init_wut@h      # Used for the initial bp if ((appFlags & 0x20) == 0)
   ori 5,5, __init_wut@l
   tw 0x1f, 30, 0           # DBGCTL_INSTRUCTION
init_wut:
   bl __init_wut
   lwz 3, 0x8(1)
   lwz 4, 0xC(1)
   bl main
   addi 1, 1, 0x10
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
