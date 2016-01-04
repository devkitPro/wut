WUT_ROOT := $(CURDIR)/../..

TARGET   := readrpl
SOURCE   := .
INCLUDE  := ../common

CXX      := g++

CPPFORMATSRC := $(wildcard $(../ext/cppformat)/*.cc)
ZLIBSRC := $(wildcard $(../ext/zlib)/*.c)

CFILES   := $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.cpp)) $(CPPFORMATSRC) $(ZLIBSRC)
INCLUDES := $(foreach dir,$(INCLUDE),-I$(dir))

CFLAGS   := -O2 -Wall --std=c++14
LDFLAGS  :=

all: $(TARGET)

clean:
	@echo "[RM] $(notdir $(TARGET))"
	@rm -rf $(TARGET)

install: all
	@echo Installing $(TARGET)
	@cp $(TARGET) $(WUT_ROOT)/bin/$(TARGET)

$(TARGET): $(CFILES)
	@echo "[CXX] $(notdir $<)"
	@$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@ $(LDFLAGS)
