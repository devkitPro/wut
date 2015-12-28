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

   /*
    * Contains the name of RPLs, referenced by .lib.rplLibs
    */
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

   .interp ALIGN(32) : { *(.interp) }
   .hash ALIGN(32) : { *(.hash) }
   .dynsym ALIGN(32) : { *(.dynsym) }
   .dynstr ALIGN(32) : { *(.dynstr) }
   .dynamic ALIGN(32) : { *(.dynamic) }
   .got ALIGN(32) : { *(.got) }
   .comment ALIGN(32) : { *(.comment) }

   /* Put all dynamic loader relocations into one section */
   .rela.dyn ALIGN(32) : {
      *(.rela.dyn)
      *(.rela.data.rplFuncStubs)
      *(.rela.lib.rplLibs)
   }

   /* Relocations for .rodata sections */
   .rela.rodata ALIGN(32) :
   {
      *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
   }

   /* Relocations for .text sections */
   .rela.text ALIGN(32) :
   {
      *(.rela.init)
      *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
      *(.rela.rplTramp.text)
      *(.rela.fini)
      *(.rela.ctors)
      *(.rela.dtors)
      *(.rela.got)
      *(.rela.toc)
   }

   /* Relocations for .data sections */
   .rela.data ALIGN(32) :
   {
      *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
   }

   /* Relocations for .bss sections */
   .rela.bss ALIGN(32) :
   {
      *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
   }

   /* Symbol tables */
   .shstrtab ALIGN(32) : { *(.shstrtab) }
   .symtab ALIGN(32) : { *(.symtab) }
   .strtab ALIGN(32) : { *(.strtab) }

   /* Standard data sections */
   . = ORIGIN(data);

   .rodata ALIGN(256) : {
      *(.rodata .rodata.*)

      KEEP (*crtbegin.o(.ctors))
      KEEP (*crtbegin?.o(.ctors))
      KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
      KEEP (*(SORT(.ctors.*)))
      KEEP (*(.ctors))

      KEEP (*crtbegin.o(.dtors))
      KEEP (*crtbegin?.o(.dtors))
      KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
      KEEP (*(SORT(.dtors.*)))
      KEEP (*(.dtors))
   } : hdr_srodata

   .data ALIGN(256) : {
      *(.data)
      *(.eh_frame)
      *(.eh_frame_hdr)
   } : hdr_sdata

   .bss ALIGN(256) : {
      *(.sbss)
      *(.bss) 
   }
}
