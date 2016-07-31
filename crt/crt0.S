.extern main
.extern exit
.global _start
_start:
	stwu 1, -0x8(1)
	stw 3, 0(1)
	stw 4, 4(1)
	bl fsDevInit
	lwz 3, 0(1)
	lwz 4, 4(1)
	bl main
	stw 3, 0(1)
	bl fsDevExit
	lwz 3, 0(1)
	addi 1, 1, 0x8
	b exit

.global __wrap___eabi
__wrap___eabi:
	blr

.global __init
__init:
	blr
