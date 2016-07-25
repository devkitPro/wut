WUT_ROOT := $(CURDIR)/..
TARGETS := libcoreinit libgx2 libnsysnet libvpad libsysapp

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
	@mkdir -p $(WUT_ROOT)/lib
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		cp $$dir/*.a $(WUT_ROOT)/lib; \
	done

.PHONY: all install clean
