WUT_ROOT := $(CURDIR)
TARGETS := crt rpl tools

all:
	@for dir in $(TARGETS); do \
		echo; \
		echo "Entering Directory $$dir"; \
		$(MAKE) --no-print-directory -C $$dir; \
		echo "Leaving Directory $$dir"; \
	done

clean:
	@rm -rf lib
	@rm -rf bin
	@for dir in $(TARGETS); do \
		echo; \
		echo Cleaning $$dir; \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install:
	@mkdir -p bin
	@mkdir -p lib
	@for dir in $(TARGETS); do \
		echo; \
		echo Installing $$dir; \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

.PHONY: all clean install
