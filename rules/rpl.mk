LIBPATHS  := -L$(WUT_ROOT)/lib -L$(DEVKITPPC)/lib
CFLAGS    := -I$(WUT_ROOT)/include -fno-builtin -ffreestanding -fno-jump-tables
CXXFLAGS  := $(CFLAGS)
LDFLAGS   := -nostartfiles -T $(WUT_ROOT)/rules/rpl.ld -pie -fPIE -z common-page-size=64 -z max-page-size=64 -lcrt \
				-Wl,-wrap,malloc,-wrap,free,-wrap,memalign,-wrap,calloc,-wrap,realloc,-wrap,malloc_usable_size \
				-Wl,-wrap,_malloc_r,-wrap,_free_r,-wrap,_realloc_r,-wrap,_calloc_r,-wrap,_memalign_r,-wrap,_malloc_usable_size_r \
				-Wl,-wrap,valloc,-wrap,_valloc_r,-wrap,_pvalloc_r,-wrap,__eabi
ELF2RPL   := $(WUT_ROOT)/bin/elf2rpl

include $(WUT_ROOT)/rules/base.mk

%.rpx: %.elf
	@echo "[RPX] $(notdir $@)"
	@$(ELF2RPL) $(BUILDDIR)/$(notdir $<) $@
