WUT_ROOT := $(CURDIR)
TARGETS := crt rpl

all:
	@for dir in $(TARGETS); do \
		echo; \
		echo "Entering Directory $$dir"; \
		$(MAKE) --no-print-directory -C $$dir; \
		echo "Leaving Directory $$dir"; \
	done
ifeq ($(OS),Windows_NT)
	@echo "Please build tools with make-tools.bat"
else
	@echo \
	@echo "Entering Directory tools"
	@$(MAKE) --no-print-directory -C tools
	@echo "Leaving Directory tools"
endif

clean:
	@rm -rf lib
	@for dir in $(TARGETS); do \
		echo Cleaning $$dir; \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install:
	@mkdir -p bin
	@mkdir -p lib
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		$(MAKE) --no-print-directory -C $$dir install; \
	done
	@cp tools/bin/* bin/

.PHONY: all clean install
