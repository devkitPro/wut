.SUFFIXES:

ifeq ($(strip $(WUT_ROOT)),)
$(error "Please ensure WUT_ROOT is in your environment.")
endif

ifeq ($(OS),Windows_NT)
CUR_DIR := $(shell cygpath -w ${CURDIR})
WUT_ROOT := $(shell cygpath -w ${WUT_ROOT})
else
CUR_DIR := $(CURDIR)
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
LDFLAGS  += -lgx2

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CUR_DIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCE),$(CUR_DIR)/$(dir)) \
                   $(foreach dir,$(DATA),$(CUR_DIR)/$(dir))
export BUILDDIR := $(CUR_DIR)
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
export INCLUDES := $(foreach dir,$(INCLUDE),-I$(CUR_DIR)/$(dir)) \
                   -I$(CUR_DIR)/$(BUILD)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CUR_DIR)/Makefile

clean:
	@echo "[RM]  $(notdir $(OUTPUT))"
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).rpx $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).rpx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

endif
