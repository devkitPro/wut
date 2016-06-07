OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(_start)

MEMORY {
   system   (rwx) : ORIGIN = 0x01000000, LENGTH = 32M
   code     (rwx) : ORIGIN = 0x02000000, LENGTH = 224M
   data     (rw)  : ORIGIN = 0x10000000, LENGTH = 800M
   load     (rwx) : ORIGIN = 0xC0000000, LENGTH = 128M
}

PHDRS {
   hdr_text    PT_LOAD  FILEHDR  PHDRS FLAGS(0x01 | 0x04);
   hdr_data    PT_LOAD                 FLAGS(0x02 | 0x04);
   hdr_srodata PT_LOAD                 FLAGS(0x04);
   hdr_sdata   PT_LOAD                 FLAGS(0x02 | 0x04);
}

SECTIONS {
   . = ORIGIN(code);

   /* Standard code section */
   .text ALIGN(32) : {
      *(.text .stub .text.*)
      *(.rplTramp.text)
      *(SORT(.rplTramp.text.*))
   } : hdr_text

   /* System stuff is for our elf2rpl converter to go through */
   . = ORIGIN(system);

   /* Contains the name of RPLs, referenced by .lib.rplLibs */
   .rodata.rplNames ALIGN(32) : {
      *(.rodata.rplNames)
   } : hdr_data

   /*
    * List of RPL libraries to import, in format:
    *   uint32_t nameAddress -> .rodata.rplNames
    *   uint32_t firstFuncEntry -> .data.rplFuncStubs
    */
   .lib.rplLibs ALIGN(32) : {
      *(.lib.rplLibs)
   }

   /*
    * List of functions an RPL exports, in format:
    *   uint32_t trampAddress
    */
   .data.rplFuncStubs ALIGN(32) : {
      *(.data.rplFuncStubs)
   }

   /* Required compiler trash */
   .got ALIGN(32) : { *(.got) }
   .hash ALIGN(32) : { *(.hash) }
   .dynsym ALIGN(32) : { *(.dynsym) }

   /* Put all dynamic loader relocations into one section */
   .rela.dyn ALIGN(32) : {
      *(.rela.dyn)
      *(.rela.data.rplFuncStubs)
      *(.rela.lib.rplLibs)
   }

   /* Relocations for .rodata sections */
   .rela.rodata ALIGN(32) :
   {
      *(.rela.rodata .rela.rodata.*)
   }

   /* Relocations for .text sections */
   .rela.text ALIGN(32) :
   {
      *(.rela.text .rela.text.*)
      *(.rela.rplTramp.text)
   }

   /* Relocations for .data sections */
   .rela.data ALIGN(32) :
   {
      *(.rela.data .rela.data.*)
   }

   /* Relocations for .bss sections */
   .rela.bss ALIGN(32) :
   {
      *(.rela.bss .rela.bss.*)
   }

   /* Symbol tables */
   .shstrtab ALIGN(32) : { *(.shstrtab) }
   .symtab ALIGN(32) : { *(.symtab) }
   .strtab ALIGN(32) : { *(.strtab) }

   /* Standard data sections */
   . = ORIGIN(data);

   .rodata ALIGN(256) : {
      *(.rodata .rodata.*)
   } : hdr_srodata

   .data ALIGN(256) : {
      *(.data)
      *(.eh_frame)
      *(.eh_frame_hdr)
   } : hdr_sdata

   .bss ALIGN(256) : {
      *(.bss)
   }

   .sdata ALIGN(256) : {
      __sdata_start = .;
      *(.sdata)
      *(.sdata.*)
      __sdata_end = .;
   }

   .sbss ALIGN(256) : {
      __sbss_start = .;
      *(.sbss)
      *(.sbss.*)
      __sbss_end = .;
   }

   .sdata2 ALIGN(256) : {
      __sdata2_start = .;
      *(.sdata2)
      *(.sdata2.*)
      __sdata2_end = .;
   }

   .sbss2 ALIGN(256) : {
      __sbss2_start = .;
      *(.sbss2)
      *(.sbss2.*)
      __sbss2_end = .;
   }

   /DISCARD/ : {
      *(.interp)
      *(.dynstr)
      *(.dynamic)
      *(.comment)
   }

   __SDATA_START__ = __sdata_start;
   __SBSS_END__ = __sbss_end;

   __SDATA2_START__ = __sdata2_start;
   __SBSS2_END__ = __sbss2_end;

   _SDA_BASE_ = __sdata_start + ((__sbss_end - __sdata_start) / 2);
   _SDA2_BASE_ = __sdata2_start + ((__sbss2_end - __sdata2_start) / 2);
}
