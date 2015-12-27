.SUFFIXES:

ifeq ($(strip $(WUT_ROOT)),)
$(error "Please ensure WUT_ROOT is in your environment.")
endif

include $(WUT_ROOT)/rules/rpl.mk

TARGET   := $(notdir $(CURDIR))
BUILD    := build
SOURCE   := src
INCLUDE  := include
DATA     := data
LIBS     := -lcoreinit

CFLAGS	 += -O2 -Wall -std=c11
CXXFLAGS += -O2 -Wall
LDFLAGS  += -lcoreinit -lgx2

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CURDIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCE),$(CURDIR)/$(dir)) \
                   $(foreach dir,$(DATA),$(CURDIR)/$(dir))
export BUILDDIR := $(CURDIR)/$(BUILD)
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
export INCLUDES := $(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir)) \
                   -I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean pkg run

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo "[RM]  $(notdir $(OUTPUT))"
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).rpx $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

endif
