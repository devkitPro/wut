OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(_start)

MEMORY {
	system (rwx) : ORIGIN = 0x01000000, LENGTH = 32M
	code (rwx) : ORIGIN = 0x02000000, LENGTH = 224M
	data (rw) : ORIGIN = 0x10000000, LENGTH = 800M
	load (rwx) : ORIGIN = 0xC0000000, LENGTH = 128M
}

PHDRS {
	hdr_text	PT_LOAD FILEHDR PHDRS   FLAGS(0x01 | 0x04);
	hdr_data	PT_LOAD					FLAGS(0x02 | 0x04);
	hdr_srodata	PT_LOAD					FLAGS(0x04);
	hdr_sdata	PT_LOAD					FLAGS(0x02 | 0x04);
}

SECTIONS {
	. = ORIGIN(code);

	/* Standard code section */
	.text ALIGN(32) : {
		*(.text .stub .text.*)
	} : hdr_text

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
	.rodata.rplNames ALIGN(32) : { *(.rodata.rplNames) } : hdr_data

	/*
	 * List of RPL libraries to import, in format:
	 *   uint32_t nameAddress -> .rodata.rplNames
	 *   uint32_t firstFuncEntry -> .data.rplFuncStubs
	 */
	.lib.rplLibs ALIGN(32) : { *(.lib.rplLibs) }

	/*
     * List of functions an RPL exports, in format:
     *   uint32_t trampAddress
	 */
	.data.rplFuncStubs ALIGN(32) : { *(.data.rplFuncStubs) }

	.interp ALIGN(32) : { *(.interp) }
	.hash ALIGN(32) : { *(.hash) }
	.dynsym ALIGN(32) : { *(.dynsym) }
	.dynstr ALIGN(32) : { *(.dynstr) }
	.rela.dyn ALIGN(32) : { *(.rela.dyn) }
	.rela.text ALIGN(32) : { *(.rela.text) }
	.eh_frame ALIGN(32) : { *(.eh_frame) }
	.dynamic ALIGN(32) : { *(.dynamic) }
	.got ALIGN(32) : { *(.got) }
	.comment ALIGN(32) : { *(.comment) }
	.shstrtab ALIGN(32) : { *(.shstrtab) }
	.symtab ALIGN(32) : { *(.symtab) }
	.strtab ALIGN(32) : { *(.strtab) }

	.rel.dyn :
	{
		*(.rel.init)
		*(.rel.text .rel.text.* .rel.gnu.linkonce.t.*)
		*(.rel.fini)
		*(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*)
		*(.rel.data.rel.ro*)
		*(.rel.data .rel.data.* .rel.gnu.linkonce.d.*)
		*(.rel.tdata .rel.tdata.* .rel.gnu.linkonce.td.*)
		*(.rel.tbss .rel.tbss.* .rel.gnu.linkonce.tb.*)
		*(.rel.ctors)
		*(.rel.dtors)
		*(.rel.got)
		*(.rel.sdata .rel.sdata.* .rel.gnu.linkonce.s.*)
		*(.rel.sbss .rel.sbss.* .rel.gnu.linkonce.sb.*)
		*(.rel.sdata2 .rel.sdata2.* .rel.gnu.linkonce.s2.*)
		*(.rel.sbss2 .rel.sbss2.* .rel.gnu.linkonce.sb2.*)
		*(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*)
	}

	.rela.dyn :
	{
		*(.rela.init)
		*(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
		*(.rela.fini)
		*(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
		*(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
		*(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
		*(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
		*(.rela.ctors)
		*(.rela.dtors)
		*(.rela.got)
		*(.rela.toc)
		*(.rela.sdata .rela.sdata.* .rela.gnu.linkonce.s.*)
		*(.rela.sbss .rela.sbss.* .rela.gnu.linkonce.sb.*)
		*(.rela.sdata2 .rela.sdata2.* .rela.gnu.linkonce.s2.*)
		*(.rela.sbss2 .rela.sbss2.* .rela.gnu.linkonce.sb2.*)
		*(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
	}

	/* Standard data sections */
	. = ORIGIN(data);

	.rodata ALIGN(256) : { *(.rodata .rodata.*) } : hdr_srodata
	.data ALIGN(256) : { *(.data) } : hdr_sdata
	.bss ALIGN(256) : { *(.sbss) *(.bss) }
}
