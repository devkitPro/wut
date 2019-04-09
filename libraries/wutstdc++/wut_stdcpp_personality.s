.section .text.__wrap___gxx_personality_v0,"ax",@progbits
.align 2

.globl __wrap___gxx_personality_v0
.type __wrap___gxx_personality_v0, @function

__wrap___gxx_personality_v0:
 .cfi_startproc
 b __real___gxx_personality_v0
 .cfi_endproc
