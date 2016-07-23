ifeq ($(shell uname -o),Cygwin)
WUT_ROOT := $(shell cygpath -w ${WUT_ROOT})
else
WUT_ROOT := $(WUT_ROOT)
endif

LIBPATHS  := -L$(WUT_ROOT)/lib
CFLAGS    := -I$(WUT_ROOT)/include -fno-builtin -ffreestanding -fno-jump-tables
CXXFLAGS  := $(CFLAGS)
LDFLAGS   := -nostdlib -nostartfiles

include $(WUT_ROOT)/rules/base.mk

%.rpx: %.elf
	@$(STRIP) $< -o $(BUILDDIR)/$(notdir $<)
