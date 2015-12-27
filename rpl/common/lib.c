#include "config.h"

// Get the start of the stubs
static const void* fstubBegin[0] __attribute__((section(".data.rplFuncStubs")));

#define EXPORT(name) \
	extern void* name; \
	const void* name##_stub __attribute__((section(".data.rplFuncStubs"))) = &name; \

#include "exports.h"

// Get the end of the stubs
static const void* fstubEnd[0] __attribute__((section(".data.rplFuncStubs")));

// Create a header with the name and stub begin/end in
typedef struct
{
	const char* name;
	const void* fstubBegin;
	const void* fstubEnd;
} __attribute__((__packed__)) rpl_header;

static const const char name[] __attribute__((section(".rodata.rplNames"))) = LIBRARY_NAME;

static rpl_header header __attribute__((section(".lib.rplLibs"))) = {
	name,
	fstubBegin,
	fstubEnd,
};
