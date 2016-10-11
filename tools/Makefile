.SUFFIXES:

TARGETS := elf2rpl readrpl implcheck

ifeq ($(OS),Windows_NT)
all:
ifeq (, $(shell which msbuild 2> /dev/null))
   $(warning "msbuild not found, try building with make-tools.bat from a vcvars prompt.")
else
	$(shell msbuild tools/tools.sln /p:Configuration=Release)
endif

clean:
ifeq (, $(shell which msbuild 2> /dev/null))
	$(shell msbuild tools/tools.sln /p:Configuration=Release /target:Clean)
else
   $(warning "msbuild not found, try building with make-tools.bat from a vcvars prompt.")
endif

install: all
	@mkdir -p $(INSTALLDIR)/bin
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		cp bin/$$dir $(INSTALLDIR)/bin; \
	done

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
	@mkdir -p $(INSTALLDIR)/bin
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		cp $$dir/$$dir $(INSTALLDIR)/bin; \
	done
endif

.PHONY: all install clean
