LIBPATHS  := -L$(WUT_ROOT)/lib
CFLAGS    := -I$(WUT_ROOT)/include -fno-builtin -ffreestanding
CXXFLAGS  := $(CFLAGS)
LDFLAGS   := -nostdlib -nostartfiles $(WUT_ROOT)/lib/crt0.o -T $(WUT_ROOT)/rules/rpl.ld -pie -fPIE

include $(WUT_ROOT)/rules/base.mk

%.rpx: %.elf
	@$(STRIP) $< -o $(BUILDDIR)/$(notdir $<)

%.rpl: %.elf
	@$(STRIP) $< -o $(BUILDDIR)/$(notdir $<)
