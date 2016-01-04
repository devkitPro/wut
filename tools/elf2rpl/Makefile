WUT_ROOT := $(CURDIR)/../..

TARGET   := elf2rpl
SOURCE   := .
INCLUDE  := ../common

CXX      := g++

CFILES   := $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.cpp))
INCLUDES := $(foreach dir,$(INCLUDE),-I$(dir))

CFLAGS   := -O2 -Wall --std=c++14
LDFLAGS  :=

all: $(TARGET)

clean:
	@echo "[RM] $(notdir $(TARGET))"
	@rm -rf $(TARGET)

install: all
	@echo Installing $(TARGET)
	@cp elf2rpl $(WUT_ROOT)/bin/elf2rpl

$(TARGET): $(CFILES)
	@echo "[CXX] $(notdir $<)"
	@$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@ $(LDFLAGS)
