.SUFFIXES:

TARGET  := $(notdir $(CURDIR))
BUILD   := build
SOURCE  := ../common .
INCLUDE := .
DATA    := data
LIBS    :=

ifneq ($(BUILD),$(notdir $(CURDIR)))
WUT_ROOT := $(CURDIR)/../..
else
WUT_ROOT := $(CURDIR)/../../..
endif
include $(WUT_ROOT)/rules/ppc.mk

LD        := $(PREFIX)ld
RPLCFLAGS := -Wno-unused-variable -fPIC -fpic -fno-builtin
CFLAGS    += -O2 -Wall -std=c11 $(RPLCFLAGS)
ODEPS     := stub.o lib.o

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CURDIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCE),$(CURDIR)/$(dir)) \
                   $(foreach dir,$(DATA),$(CURDIR)/$(dir))
export BUILDDIR := $(CURDIR)/$(BUILD)
export DEPSDIR  := $(BUILDDIR)

CFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES  := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))

export OFILES := $(CFILES:.c=.o) \
                 $(CXXFILES:.cpp=.o) \
                 $(SFILES:.S=.o)

export INCLUDES := $(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir)) \
                   -I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo "[RM] $(notdir $(OUTPUT))"
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).a

else

DEPENDS := $(OFILES:.o=.d)
OFILES  := $(filter-out $(ODEPS),$(OFILES))

$(OUTPUT).a: rpl.o $(OFILES)

lib.o: lib.c
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(DEPSOPTIONS) $(RPLCFLAGS) -S $(INCLUDES) $< -o lib.S
	@$(CC) $(DEPSOPTIONS) $(RPLCFLAGS) -c lib.S -o $@

rpl.o: $(ODEPS)
	@$(LD) $(LDFLAGS) -r $(ODEPS) -o $@

-include $(DEPENDS)

endif
