.SUFFIXES:

ifeq ($(shell uname -o),Cygwin)
CUR_DIR := $(shell cygpath -w ${CURDIR})
else
CUR_DIR := $(CURDIR)
endif

TARGET  := $(notdir $(CUR_DIR))
BUILD   := build
SOURCE  := ../common .
INCLUDE := .
DATA    := data
LIBS    :=

ifneq ($(BUILD),$(notdir $(CURDIR)))
WUT_ROOT := $(CUR_DIR)/../..
else
WUT_ROOT := $(CUR_DIR)/../../..
endif
include $(WUT_ROOT)/rules/ppc.mk

LD        := $(PREFIX)ld
RPLCFLAGS := -Wno-unused-variable -fno-builtin
CFLAGS    += -O2 -Wall -std=c11 $(RPLCFLAGS)
ODEPS     := stub.o lib.o

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CUR_DIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCE),$(CUR_DIR)/$(dir)) \
                   $(foreach dir,$(DATA),$(CUR_DIR)/$(dir))
export BUILDDIR := $(CUR_DIR)/$(BUILD)
export DEPSDIR  := $(BUILDDIR)

CFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES  := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))

export OFILES := $(CFILES:.c=.o) \
                 $(CXXFILES:.cpp=.o) \
                 $(SFILES:.S=.o)

export INCLUDES := $(foreach dir,$(INCLUDE),-I$(CUR_DIR)/$(dir)) \
                   -I$(CUR_DIR)/$(BUILD)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CUR_DIR)/Makefile

clean:
	@echo "[RM] $(notdir $(OUTPUT))"
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).a

else

DEPENDS := $(OFILES:.o=.d)
OFILES  := $(filter-out $(ODEPS),$(OFILES))

$(OUTPUT).a: rpl.o $(OFILES)

lib.c: exports.h

lib.o: lib.c exports.h
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(EXTRA_OPTIONS) $(RPLCFLAGS) -S $(INCLUDES) $< -o lib.S
	@$(CC) $(EXTRA_OPTIONS) $(RPLCFLAGS) -c lib.S -o $@

rpl.o: $(ODEPS)
	@$(LD) $(EXTRA_OPTIONS) $(LDFLAGS) -r $(ODEPS) -o $@

-include $(DEPENDS)

endif
