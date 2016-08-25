include $(CURDIR)/../rules/ppc.mk

CFILES  := $(wildcard *.c)
SFILES  := $(wildcard *.S)
OFILES  := $(CFILES:.c=.o) $(SFILES:.S=.o)
OUTPUT  := libcrt

all: $(OUTPUT).a $(OFILES)

clean:
	@echo "[RM] $(notdir $(OUTPUT))"
	@rm -f $(OFILES) $(OUTPUT).a

install: all
	@mkdir -p $(INSTALLDIR)/lib
	@cp -f *.a $(INSTALLDIR)/lib

%.o: %.S
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT).a: $(OFILES)

.PHONY: all clean
