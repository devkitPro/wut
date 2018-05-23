OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

MEMORY {
   relmem  (rw)  : ORIGIN = 0x00000000, LENGTH = 32M
   codemem (rwx) : ORIGIN = 0x02000000, LENGTH = 224M
   datamem (rw)  : ORIGIN = 0x10000000, LENGTH = 800M
   loadmem (rwx) : ORIGIN = 0xC0000000, LENGTH = 128M
}

EXTERN(main)
ENTRY(main)

SECTIONS
{
   . = ORIGIN(codemem);
   .syscall ALIGN(32) : {
      *(.syscall .syscall.*)
   } > codemem

   .text ALIGN(32) : {
      *(.text .text.*)
      *(.init)
      *(.fini)
   } > codemem

   . = ORIGIN(datamem);
   .rodata ALIGN(32) : {
      *(.rodata .rodata.*)
      *(.ctors)
      *(.dtors)
      *(.init_array)
      *(.fini_array)
      *(.jcr)
      *(.gcc_except_table .gcc_except_table.*)
      *(.eh_frame_hdr)
      *(.eh_frame)
      *(.got)
      *(.got1)
      *(.got2)
      *(.tm_clone_table)
   } > datamem

   .data ALIGN(32) : {
      *(.data .data.*)

      . = ALIGN(32);
      __sdata_start = .;
      *(.sdata .sdata.*)
      __sdata_end = .;

      . = ALIGN(32);
      __sdata2_start = .;
      *(.sdata2 .sdata2.*)
      __sdata2_end = .;
   } > datamem

   __bss_start = .;
   .bss ALIGN(64) : {
      *(.bss .bss.*)

      . = ALIGN(64);
      __sbss_start = .;
      *(.sbss .sbss.*)
      __sbss_end = .;

      . = ALIGN(64);
      __sbss2_start = .;
      *(.sbss2 .sbss2.*)
      __sbss2_end = .;
   }
   __bss_end = .;

   . = ORIGIN(relmem);
   .rela.text ALIGN(4) : {
      *(.rela.text .rela.text.*)
      *(.rela.init)
      *(.rela.fini)
   } > relmem
   .rela.data ALIGN(4) : {
      *(.rela.data .rela.data.*)
      *(.rela.sdata)
      *(.rela.sdata2)
      *(.rela.init_array)
      *(.rela.fini_array)
      *(.rela.gcc_except_table .rela.gcc_except_table.*)
      *(.rela.eh_frame)
      *(.rela.got2)
   } > relmem
   .rela.rodata ALIGN(4) : {
      *(.rela.rodata .rela.rodata.*)
   } > relmem

   . = ORIGIN(loadmem);
   .fimport_coreinit ALIGN(16) : {
      *(.fimport_coreinit)
   } > loadmem
   .fimport_gx2 ALIGN(16) : {
      *(.fimport_gx2)
   } > loadmem
   .fimport_nn_ac ALIGN(16) : {
      *(.fimport_nn_ac)
   } > loadmem
   .fimport_nsysnet ALIGN(16) : {
      *(.fimport_nsysnet)
   } > loadmem
   .fimport_proc_ui ALIGN(16) : {
      *(.fimport_proc_ui)
   } > loadmem
   .fimport_sndcore2 ALIGN(16) : {
      *(.fimport_sndcore2)
   } > loadmem
   .fimport_sysapp ALIGN(16) : {
      *(.fimport_sysapp)
   } > loadmem
   .fimport_vpad ALIGN(16) : {
      *(.fimport_vpad)
   } > loadmem

   .symtab ALIGN(4) : {
      *(.symtab)
   } > loadmem
   .strtab ALIGN(1) : {
      *(.strtab)
   } > loadmem
   .shstrtab ALIGN(1) : {
      *(.shstrtab)
   } > loadmem

   __SDATA_START__ = __sdata_start;
   __SBSS_END__ = __sbss_end;

   __SDATA2_START__ = __sdata2_start;
   __SBSS2_END__ = __sbss2_end;

   _SDA_BASE_ = __sbss_end;
   _SDA2_BASE_ = __sdata2_start + ((__sbss2_end - __sdata2_start) / 2);

   /DISCARD/ : {
      *(.comment)
      *(.fixup)
      *(.gnu.attributes)
      *(.abs)
   }
}
