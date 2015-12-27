.extern main
.extern _Exit
.global _start
_start:
	bl main
	b _Exit

.global __eabi
__eabi:
	blr
