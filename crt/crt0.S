.extern main
.extern exit
.global _start
_start:
	bl main
	b exit

.global __wrap___eabi
__wrap___eabi:
	blr
	
.global __init
__init:
	blr
