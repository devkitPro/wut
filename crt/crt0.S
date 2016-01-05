.extern main
.extern exit
.global _start
_start:
	bl main
	b exit

.global __eabi
__eabi:
	blr
