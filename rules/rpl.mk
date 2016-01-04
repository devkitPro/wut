LIBPATHS  := -L$(WUT_ROOT)/lib
CFLAGS    := -I$(WUT_ROOT)/include -fno-builtin -ffreestanding
CXXFLAGS  := $(CFLAGS)
LDFLAGS   := -nostdlib -nostartfiles $(WUT_ROOT)/lib/crt0.o -T $(WUT_ROOT)/rules/rpl.ld -pie -fPIE -z common-page-size=64 -z max-page-size=64
ELF2RPL   := $(WUT_ROOT)/bin/elf2rpl

include $(WUT_ROOT)/rules/base.mk

%.rpx: %.elf
	@echo "[RPX] $(notdir $@)"
	@$(ELF2RPL) $(BUILDDIR)/$(notdir $<) $@
