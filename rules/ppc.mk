LIBPATHS  := -L$(WUT_ROOT)/lib
CFLAGS    := -I$(WUT_ROOT)/include -fno-builtin -ffreestanding
CXXFLAGS  := $(CFLAGS)
LDFLAGS   := -nostdlib -nostartfiles -T $(WUT_ROOT)/rules/rpl.ld

include $(WUT_ROOT)/rules/base.mk

%.rpx: %.elf
	@$(STRIP) $< -o $(BUILDDIR)/$(notdir $<)
