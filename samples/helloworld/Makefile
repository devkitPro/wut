.SUFFIXES:

ifeq ($(strip $(WUT_ROOT)),)
$(error "Please ensure WUT_ROOT is in your environment.")
endif

ifeq ($(shell uname -o),Cygwin)
ROOT := $(shell cygpath -w ${CURDIR})
WUT_ROOT := $(shell cygpath -w ${WUT_ROOT})
else
ROOT := $(CURDIR)
endif

include $(WUT_ROOT)/rules/rpl.mk

TARGET   := $(notdir $(CURDIR))
BUILD    := build
SOURCE   := src
INCLUDE  := include
DATA     := data
LIBS     := -lcoreinit -lproc_ui -lsysapp

CFLAGS   += -O2 -Wall -std=c11
CXXFLAGS += -O2 -Wall

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(ROOT)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCE),$(ROOT)/$(dir)) \
                   $(foreach dir,$(DATA),$(ROOT)/$(dir))
export BUILDDIR := $(ROOT)
export DEPSDIR  := $(BUILDDIR)

CFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES  := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES    := $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))

ifeq ($(strip $(CXXFILES)),)
export LD := $(CC)
else
export LD := $(CXX)
endif

export OFILES := $(CFILES:.c=.o) \
                 $(CXXFILES:.cpp=.o) \
                 $(SFILES:.S=.o)
export INCLUDES := $(foreach dir,$(INCLUDE),-I$(ROOT)/$(dir)) \
                   -I$(ROOT)/$(BUILD)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(ROOT)/Makefile

clean:
	@echo "[RM]  $(notdir $(OUTPUT))"
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).rpx $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).rpx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

endif
