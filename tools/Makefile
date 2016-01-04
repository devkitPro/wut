.SUFFIXES:

WUT_ROOT := $(CURDIR)/..
TARGETS := elf2rpl

ifeq ($(OS),Windows_NT)
all:
	@echo "Please build tools with make-tools.bat"

install:
	@echo "Please build tools with make-tools.bat"

clean:
	@echo "Please build tools with make-tools.bat"
else
all:
	@for dir in $(TARGETS); do \
		echo; \
		echo Entering Directory $$dir; \
		$(MAKE) --no-print-directory -C $$dir; \
		echo Leaving Directory $$dir; \
	done

clean:
	@for dir in $(TARGETS); do \
		echo Cleaning $$dir; \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install: all
	@mkdir -p $(WUT_ROOT)/bin
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		cp $$dir/$$dir $(WUT_ROOT)/bin; \
	done
endif

.PHONY: all install clean
