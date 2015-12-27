ifeq ($(strip $(DEVKITPRO)),)
$(error "Please ensure DEVKITPRO is in your environment.")
endif

ifeq ($(strip $(DEVKITPPC)),)
$(error "Please ensure DEVKITPPC is in your environment.")
endif

export PORTLIBS := $(DEVKITPRO)/portlibs/ppc
export PATH := $(DEVKITPPC)/bin:$(PORTLIBS)/bin:$(PATH)

PREFIX  := powerpc-eabi-
OBJCOPY := $(PREFIX)objcopy
AR      := $(PREFIX)ar
AS      := $(PREFIX)gcc
CC      := $(PREFIX)gcc
CXX     := $(PREFIX)g++
STRIP   := $(PREFIX)strip

ifeq ($(findstring $(PREFIX),$(LD)),)
LD := $(CC)
endif

DEPSOPTIONS = -MMD -MP -MF $(DEPSDIR)/$*.d

ifdef VERBOSE
DEPSOPTIONS += -v
endif

%.o: %.c
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(DEPSOPTIONS) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	@echo "[CXX] $(notdir $<)"
	@$(CXX) $(DEPSOPTIONS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	@echo "[CC]  $(notdir $<)"
	@$(AS) $(DEPSOPTIONS) -x assembler-with-cpp $(ASFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.S
	@echo "[CC]  $(notdir $<)"
	@$(AS) $(DEPSOPTIONS) -x assembler-with-cpp $(ASFLAGS) $(INCLUDES) -c $< -o $@

%.a:
	@echo "[AR]  $(notdir $@)"
	@$(AR) -rcs $@ $^

%.elf:
	@echo "[LD]  $(notdir $@)"
	@echo "[LD]  $(LIBPATHS)"
	@echo "[LD]  $(LDFLAGS)"
	@$(LD) -v $^ $(LIBPATHS) $(LIBS) $(LDFLAGS) -o $@
