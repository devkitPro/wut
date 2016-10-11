ifeq ($(findstring CYGWIN,$(shell uname -s)),CYGWIN)
WUT_ROOT := $(shell cygpath -w ${CURDIR})
RPL_ROOT := $(shell cygpath -w ${SYSTEM_RPL_ROOT})
else
WUT_ROOT := $(CURDIR)
RPL_ROOT := $(SYSTEM_RPL_ROOT)
endif

TARGETS := tools crt rpl

DESTDIR ?= $(CURDIR)
INSTALLDIR := $(DESTDIR)

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
	@for dir in $(TARGETS); do \
		echo; \
		echo Cleaning $$dir; \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install:
	@mkdir -p $(INSTALLDIR)
	@cp -r include $(INSTALLDIR) || :
	@for dir in $(TARGETS); do \
		echo; \
		echo Installing $$dir; \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

test: all
	@tools/bin/implcheck $(RPL_ROOT)\coreinit.rpl rpl\libcoreinit\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\gx2.rpl rpl\libgx2\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\nsysnet.rpl rpl\libnsysnet\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\proc_ui.rpl rpl\libproc_ui\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\sndcore2.rpl rpl\libsndcore2\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\sysapp.rpl rpl\libsysapp\exports.h
	@tools/bin/implcheck $(RPL_ROOT)\vpad.rpl rpl\libvpad\exports.h

.PHONY: all clean install
