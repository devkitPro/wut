ifeq ($(findstring CYGWIN,$(shell uname -s)),CYGWIN)
WUT_ROOT := $(shell cygpath -w ${CURDIR})
else
WUT_ROOT := $(CURDIR)
endif

TARGETS := tools crt rpl

DESTDIR ?= $(CURDIR)
INSTALLDIR := $(shell cd ${DESTDIR} ; pwd)

export WUT_ROOT
export INSTALLDIR

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
	@mkdir -p $(INSTALLDIR)
	@cp -r include $(INSTALLDIR)
	@for dir in $(TARGETS); do \
		echo; \
		echo Installing $$dir; \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

.PHONY: all clean install
