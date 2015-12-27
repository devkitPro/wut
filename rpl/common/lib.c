#include "config.h"

typedef struct {
	const char* name;
	const void* fstub;
} __attribute__((__packed__)) rpl_header;

static const void* fstub[0] __attribute__((section(".data.rplFuncStubs")));
static const const char name[] __attribute__((section(".rodata.rplNames"))) = LIBRARY_NAME;

static rpl_header header __attribute__((section(".lib.rplLibs"))) = {
	name,
	fstub,
};

#define EXPORT(name) \
	extern void* name; \
	const void* name##_stub __attribute__((section(".data.rplFuncStubs"))) = &name; \

#include "exports.h"
