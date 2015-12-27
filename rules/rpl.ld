OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(_start)

MEMORY {
	system (rw) : ORIGIN = 0x01000000, LENGTH = 32M
	code (rwx) : ORIGIN = 0x02000000, LENGTH = 224M
	data (rw) : ORIGIN = 0x10000000, LENGTH = 800M
}

PHDRS {
}

SECTIONS {
	. = ORIGIN(code);

	/* Standard code section */
	.text ALIGN(32) : { *(.text .stub .text.*) }

	/*
	 * Trampolines for each RPL function, have the same symbol name of
	 * than the function they should import.
	 *
	 * There will be 2 relocations in each trampoline pointing to the
	 * function stub inside the .data.rplFuncStubs, we can edit these
	 * relocation entries to use the RPL import during conversion to RPL.
	 *
	 *   li    r0, func_stub@lo -> .data.rplFuncStubs
	 *   oris  r0, func_stub@hi -> .data.rplFuncStubs
	 *   mtctr r0
	 *   bctr
	 */
	.rplTramp.text ALIGN(32) : {
		*(.rplTramp.text)
		*(SORT(.rplTramp.text.*))
	}

	/* System stuff is for our elf2rpl converter to go through */
	. = ORIGIN(system);

	/*
     * Contains the name of RPLs, referenced by .lib.rplLibs
     */
	.rodata.rplNames ALIGN(32) : { KEEP (*(.rodata.rplNames)) }

	/*
	 * List of RPL libraries to import, in format:
	 *   uint32_t nameAddress -> .rodata.rplNames
	 *   uint32_t firstFuncEntry -> .data.rplFuncStubs
	 */
	.lib.rplLibs ALIGN(32) : { KEEP (*(.lib.rplLibs)) }

	/*
     * List of functions an RPL exports, in format:
     *   uint32_t trampAddress
	 */
	.data.rplFuncStubs ALIGN(32) : { KEEP (*(.data.rplFuncStubs)) }

	/* Standard data sections */
	. = ORIGIN(data);

	.rodata ALIGN(256) : { *(.rodata .rodata.*) }
	.data ALIGN(256) : { *(.data) }
	.bss ALIGN(256) : { *(.bss) }
}
