# wut makefile beta - let's just stick with cmake, yeah?
# should work for out-of-tree builds
# Scroll to the bottom for predefined/utility variables

# If V isn't given as 1 on the commandline, prepend "@" onto all our commands
# See uses of $(Q) later - this stops make echoing our commands
ifneq ($(strip $(V)), 1)
	Q ?= @
endif

# ------------------------------------------------------------------------------
# Toolchain includes and path setup

# Make sure we have devkitPPC
ifeq ($(strip $(DEVKITPRO)),)
	$(error "Please set DEVKITPRO in your environment.")
endif

# May as well have a guess. ?= means an existing DEVKITPPC value isn't touched.
export DEVKITPPC ?= $(DEVKITPRO)/devkitPPC

# Pull in devkitPPC bits - this gets $(CC) and friends set up
include $(DEVKITPPC)/base_tools

# Make sure we have wut
ifeq ($(strip $(WUT_ROOT)),)
	$(error "Please set WUT_ROOT in your environment.")
endif

# Grab wut tools we need.
WUT_ELF2RPL := $(DEVKITPRO)/tools/bin/elf2rpl
WUT_RPLEXPORTGEN := $(DEVKITPRO)/tools/bin/rplexportgen

# If DEPSDIR isn't defined, assume this is an out-of-tree build and that we're
# already running in the build folder - thus, put deps in CURDIR
DEPSDIR ?= $(CURDIR)

# Default to .d for depends
DEPSEXT ?= d

# ------------------------------------------------------------------------------
# Get our flags in order
# There's some default wut flags, they need to be added

# cpu type and hardware flags, keep all relocations (for elf2rpl), wut includes
WUT_CFLAGS  := -mcpu=750 -meabi -mhard-float -isystem $(WUT_ROOT)/include
# Defines to tell code about this environment
WUT_CFLAGS  += -D__WIIU__ -D__WUT__ -D__WUT_MAKEFILE__
# keep relocations, use wut linker script
WUT_LDFLAGS := -Wl,-q -Wl,-z,nocopyreloc -T $(WUT_ROOT)/share/wut.ld
# Path for wut libraries, Always link against coreinit
WUT_LDFLAGS += -L$(WUT_ROOT)/lib -lcoreinit

# Append that to user-provided cflags and others
CFLAGS    += $(WUT_CFLAGS)
CXXFLAGS  += $(WUT_CFLAGS)
OBJCFLAGS += $(WUT_CFLAGS)
# assembler-with-cpp allows using #defines and stuff in Assembly source
# It's forced on devkitPPC, so it's forced here
ASFLAGS   += $(WUT_CFLAGS) -x assembler-with-cpp
LDFLAGS   += $(WUT_LDFLAGS)

# Linking sucks... this make the ordering of libraries irrelevant, but the
# manuals reckon it's not good for performance. Set WUT_NO_LDGROUPS=1 to disable
# or DIY this bit (_PRE and _POST are included no matter what)
ifneq ($(strip $(WUT_NO_LDGROUPS)), 1)
	LDFLAGS_PRE += -Wl,--start-group
	LDFLAGS_POST += -Wl,--end-group
endif

# RPX and RPL need slightly different crts (init code)
%.rpx: LDFLAGS += -lwutcrt
%.rpl: LDFLAGS += -lwutcrtrpl

# ------------------------------------------------------------------------------
# Linking bits

# What should we call files that have been linked but not run through elf2rpl?
WUT_RPLELF_SUFFIX := .elf

# If we're making an rpl, pass --rpl into elf2rpl
%.rpl: WUT_ELF2RPLFLAGS += --rpl

# Main RPX/RPL linking rule. This process is basically identical for both types,
# aside from a few flags (which we've already set)
%.rpx %.rpl:
# Use CXX to link our initial output file, ready for elf2rpl
	@echo LD $(notdir $@)$(WUT_RPLELF_SUFFIX)
	$(Q)$(CXX) $^ $(LDFLAGS_PRE) $(LDFLAGS) $(LDFLAGS_POST) -o $@$(WUT_RPLELF_SUFFIX)
	$(Q)if [ "$(WUT_NO_STRIP)" = "" ]; then \
		echo STRIP $(notdir $@)$(WUT_RPLELF_SUFFIX); \
		$(PREFIX)strip -g $@$(WUT_RPLELF_SUFFIX); \
	fi
# Run elf2rpl on it
	@echo ELF2RPL $(notdir $@)
	$(Q)$(WUT_ELF2RPL) $(WUT_ELF2RPLFLAGS) $@$(WUT_RPLELF_SUFFIX) $@
# Unless we're told not to, delete the initial output file
	$(Q)if [ "$(WUT_KEEP_RPLELF)" = "" ]; then \
		rm -f $@$(WUT_RPLELF_SUFFIX); \
	fi

# ------------------------------------------------------------------------------
# Compilation rules
# Bog-standard compilation rules. Only using these and not devkitPPC's
# base_rules because the mkdir bits are needed

# Allow turning off the compilation rules
ifneq ($(strip $(WUT_NO_COMPRULES)), 1)

%.o: %.cpp
	@echo CXX $(notdir $<)
	@mkdir -p $(dir $*)
	$(Q)$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.$(DEPSEXT) $(CXXFLAGS) -c $< -o $@ $(ERROR_FILTER)

%.o: %.c
	@echo CC $(notdir $<)
	@mkdir -p $(dir $*)
	$(Q)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.$(DEPSEXT) $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)

%.o: %.m
	@echo CC $(notdir $<)
	@mkdir -p $(dir $*)
	$(Q)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.$(DEPSEXT) $(OBJCFLAGS) -c $< -o $@ $(ERROR_FILTER)

%.o: %.s
	@echo CC $(notdir $<)
	@mkdir -p $(dir $*)
	$(Q)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.$(DEPSEXT)  $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

%.o: %.S
	@echo CC $(notdir $<)
	@mkdir -p $(dir $*)
	$(Q)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.$(DEPSEXT) $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

%.a:
	@echo AR $(notdir $@)
	@mkdir -p $(dir $*)
	@rm -f $@
	$(Q)$(AR) -rc $@ $^

endif

# Allow turning off the depend rules
ifneq ($(strip $(WUT_NO_DEPEND_INCS)), 1)

# Add the dependency rules, if they exist
include $(shell find $(DEPSDIR) -name "*.$(DEPSEXT)")

endif

# ------------------------------------------------------------------------------
# Optional Extras
# Maybe you want libc/newlib? or a devoptab? These contain the flags you need to
# do it.

# Enable newlib support, making more complex libc functions work. Basic stuff
# like memset doesn't need this, but time functions and malloc do.
# Unless you also use WUT_MALLOC_LDFLAGS, this will dedicate most of the default
# Cafe heap to libc malloc.
# To use:
#  LDFLAGS += $(WUT_NEWLIB_LDFLAGS)
WUT_NEWLIB_LDFLAGS := -Wl,--whole-archive -lwutnewlib -Wl,--no-whole-archive

# Wrap calls to malloc and friends with calls to Cafe's MEMDefaultHeap
# functions, effectivley bypassing the libc heap for most allocations. Forces
# libc heap to be very small.
# To use:
#  LDFLAGS += $(WUT_MALLOC_LDFLAGS)
WUT_MALLOC_LDFLAGS := -Wl,--whole-archive -lwutmalloc -Wl,--no-whole-archive

# Enable libstdc++ support. Allows use of C++11 threads, along with other C++
# functionality. Make sure to use WUT_NEWLIB_LDFLAGS too.
# To use:
#  LDFLAGS += $(WUT_STDCPP_LDFLAGS)
WUT_STDCPP_LDFLAGS := -lstdc++
WUT_STDCPP_LDFLAGS += -Wl,--whole-archive -lwutstdc++ -Wl,--no-whole-archive

# Simple devoptab to allow filesystem access. Mounts the SD alongside the default
# Cafe mounts (/vol/content etc.)
# To use:
#  LDFLAGS += $(WUT_DEVOPTAB_LDFLAGS)
WUT_DEVOPTAB_LDFLAGS := -Wl,--whole-archive -lwutdevoptab -Wl,--no-whole-archive
