OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

MEMORY {
   relmem  (rw)  : ORIGIN = 0x00000000, LENGTH = 32M
   codemem (rwx) : ORIGIN = 0x02000000, LENGTH = 224M
   datamem (rw)  : ORIGIN = 0x10000000, LENGTH = 800M
   loadmem (rwx) : ORIGIN = 0xC0000000, LENGTH = 128M
}

EXTERN(_start)
ENTRY(_start)

SECTIONS
{
   . = ORIGIN(codemem);
   .syscall ALIGN(32) : {
      *(.syscall .syscall.*)
   } > codemem

   .text ALIGN(32) : {
      KEEP (*crt0.o(*.init))
      KEEP (*(.init))

      *(.text)
      *(.text.*)
      *(.gnu.warning)
      *(.gnu.linkonce.t.*)

      KEEP (*(.fini))
   } > codemem

   . = ORIGIN(datamem);
   .rodata ALIGN(32) : {
      *(.rodata)
      *(.rodata.*)
      *(.gnu.linkonce.r.*)

      *(.preinit_array)
      *(.init_array)
      *(.fini_array)

      KEEP (*crtbegin.o(.ctors))
      KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
      KEEP (*(SORT(.ctors.*)))
      KEEP (*(.ctors))

      KEEP (*crtbegin.o(.dtors))
      KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
      KEEP (*(SORT(.dtors.*)))
      KEEP (*(.dtors))

      *(.jcr)
      *(.dynamic)
      *(.eh_frame_hdr)
      KEEP (*(.eh_frame))
      *(.fixup)
      *(.gcc_except_table)
      *(.gcc_except_table.*)
      *(.got)
      *(.got1)
      *(.got2)
      *(.got.plt)
      *(.plt)
      *(.tm_clone_table)
   } > datamem

   .data ALIGN(32) : {
      *(.data)
      *(.data.*)
      *(.gnu.linkonce.d.*)
      SORT(CONSTRUCTORS)

      . = ALIGN(32);
      __sdata_start = .;
      *(.sdata)
      *(.sdata.*)
      *(.gnu.linkonce.s.*)
      . = ALIGN(32);
      __sdata_end = .;

      __sdata2_start = .;
      *(.sdata2)
      *(.sdata2.*)
      *(.gnu.linkonce.s2.*)
      . = ALIGN(32);
      __sdata2_end = .;
   } > datamem

   __bss_start = .;
   .bss ALIGN(64) : {
      *(.dynbss)
      *(.bss)
      *(.bss.*)
      *(.gnu.linkonce.b.*)
      *(COMMON)

      . = ALIGN(64);
      __sbss_start = .;
      *(.dynsbss)
      *(.sbss)
      *(.sbss.*)
      *(.gnu.linkonce.sb.*)
      *(.scommon)
      __sbss_end = .;

      . = ALIGN(64);
      __sbss2_start = .;
      *(.sbss2)
      *(.sbss2.*)
      *(.gnu.linkonce.sb2.*)
      __sbss2_end = .;


      . = ALIGN(32);
   }
   __bss_end = .;

   . = ORIGIN(relmem);
   .rela.text ALIGN(4) : {
      *(.rela.text)
      *(.rela.text.*)
      *(.rela.gnu.linkonce.t.*)
      *(.rela.init)
      *(.rela.fini)
   } > relmem
   .rela.data ALIGN(4) : {
      *(.rela.data)
      *(.rela.data.*)
      *(.rela.gnu.linkonce.d.*)
      *(.rela.sdata)
      *(.rela.gnu.linkonce.s.*)
      *(.rela.sdata2)
      *(.rela.gnu.linkonce.s2.*)
      *(.rela.init_array)
      *(.rela.fini_array)
      *(.rela.gcc_except_table .rela.gcc_except_table.*)
      *(.rela.eh_frame)
      *(.rela.got)
      *(.rela.got1)
      *(.rela.got2)
      *(.rela.got.plt)
      *(.rela.plt)
   } > relmem
   .rela.rodata ALIGN(4) : {
      *(.rela.rodata)
      *(.rela.rodata.*)
      *(.rel.gnu.linkonce.r.*)
      *(.rela.ctors)
      *(.rela.dtors)
   } > relmem

   . = ORIGIN(loadmem);
   .fexports ALIGN(32) : {
      *(.fexports)
   } > loadmem
   .dexports ALIGN(32) : {
      *(.dexports)
   } > loadmem

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

   .dimport_coreinit ALIGN(16) : {
      *(.dimport_coreinit)
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
      *(.abs)
      *(.comment)
      *(.gnu.attributes)
      *(.gnu.version)
      *(.gnu.version_d)
      *(.gnu.version_r)
   }
}
