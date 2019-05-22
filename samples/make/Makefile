MAKEFILES	:=	$(shell find . -mindepth 2 -name Makefile)

DATESTRING	:=	$(shell date +%Y)$(shell date +%m)$(shell date +%d)

all:
	@for i in $(MAKEFILES); do $(MAKE) -C `dirname $$i` || exit 1; done;

clean:
	@for i in $(MAKEFILES); do $(MAKE) -C `dirname $$i` clean || exit 1; done;
