WUT_ROOT := $(CURDIR)/..
include $(WUT_ROOT)/rules/ppc.mk

CFILES  := $(wildcard *.c)
SFILES  := $(wildcard *.S)
CRT0    := crt0.o

STUBS   := $(SFILES:.S=.o) $(CFILES:.c=.o)

all: $(STUBS) $(CRT0)

clean:
	@echo "[RM] $(notdir $(CRT0))"
	@rm -f $(STUBS) $(CRT0)

install: all
	@mkdir -p $(WUT_ROOT)/lib
	@cp -f *.o $(WUT_ROOT)/lib

%.o: %.S
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean
