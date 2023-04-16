
TOPDIR ?= $(CURDIR)
include $(TOPDIR)/share/wut_rules

export WUT_MAJOR	:=	1
export WUT_MINOR	:=	3
export WUT_PATCH	:=	0

VERSION	:=	$(WUT_MAJOR).$(WUT_MINOR).$(WUT_PATCH)

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
TARGET		:=	wut
#BUILD		:=	build
SOURCES		:=	cafe \
				libraries/wutcrt \
				libraries/wutnewlib \
				libraries/wutstdc++ \
				libraries/wutmalloc \
				libraries/wutdevoptab \
				libraries/wutsocket \
				libraries/wutdefaultheap \
				libraries/libwhb/src \
				libraries/libgfd/src \
				libraries/libirc/src \
				libraries/nn_erreula \
				libraries/nn_swkbd
DATA		:=	data
INCLUDES	:=	include \
				libraries/libwhb/include \
				libraries/libgfd/include \
				libraries/libirc/include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	:=	-g -Wall -Werror \
			-ffunction-sections -fdata-sections \
			$(MACHDEP) \
			$(BUILD_CFLAGS)

CFLAGS	+=	$(INCLUDE) -D__WIIU__ -D__WUT__

CXXFLAGS	:= $(CFLAGS) -std=gnu++17 -fno-exceptions -fno-rtti

ASFLAGS	:=	-g $(MACHDEP)

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
DEFFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.def)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SRC	:=	$(DEFFILES:.def=.o) $(SFILES:.s=.o) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
export OFILES 	:=	$(OFILES_BIN) $(OFILES_SRC)
export HFILES	:=	$(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I.

.PHONY: all dist-bin dist-src dist install clean

#---------------------------------------------------------------------------------
all: lib/libwut.a lib/libwutd.a

dist-bin: all
	@tar --exclude=*~ -cjf wut-$(VERSION).tar.bz2 \
		include lib share \
		-C libraries/libwhb include \
		-C ../libgfd include \
		-C ../libirc include

dist-src:
	@tar --exclude=*~ -cjf wut-src-$(VERSION).tar.bz2 cafe include libraries share Makefile

dist: dist-src dist-bin

install: dist-bin
	mkdir -p $(DESTDIR)$(DEVKITPRO)/wut
	bzip2 -cd wut-$(VERSION).tar.bz2 | tar -xf - -C $(DESTDIR)$(DEVKITPRO)/wut

lib:
	@[ -d $@ ] || mkdir -p $@

release:
	@[ -d $@ ] || mkdir -p $@

debug:
	@[ -d $@ ] || mkdir -p $@

lib/libwut.a : lib release $(SOURCES) $(INCLUDES)
	@$(MAKE) BUILD=release OUTPUT=$(CURDIR)/$@ \
	BUILD_CFLAGS="-DNDEBUG=1 -O2" \
	DEPSDIR=$(CURDIR)/release \
	--no-print-directory -C release \
	-f $(CURDIR)/Makefile

lib/libwutd.a : lib debug $(SOURCES) $(INCLUDES)
	@$(MAKE) BUILD=debug OUTPUT=$(CURDIR)/$@ \
	BUILD_CFLAGS="-DDEBUG=1 -Og" \
	DEPSDIR=$(CURDIR)/debug \
	--no-print-directory -C debug \
	-f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -rf release debug lib

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT)	:	$(OFILES)

$(OFILES_SRC)	: $(HFILES)

#---------------------------------------------------------------------------------
%_bin.h %.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
