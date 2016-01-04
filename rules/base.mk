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

EXTRA_OPTIONS = 

ifdef VERBOSE
EXTRA_OPTIONS += -v
endif

%.o: %.c
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(EXTRA_OPTIONS) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	@echo "[CXX] $(notdir $<)"
	@$(CXX) $(EXTRA_OPTIONS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	@echo "[CC]  $(notdir $<)"
	@$(AS) $(EXTRA_OPTIONS) -x assembler-with-cpp $(ASFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.S
	@echo "[CC]  $(notdir $<)"
	@$(AS) $(EXTRA_OPTIONS) -x assembler-with-cpp $(ASFLAGS) $(INCLUDES) -c $< -o $@

%.a:
	@echo "[AR]  $(notdir $@)"
	@$(AR) -rcs $@ $^

%.elf: $(OFILES)
	@echo "[LD]  $(notdir $@)"
	@$(LD) $^ $(LIBPATHS) $(LIBS) $(LDFLAGS) -o $@
