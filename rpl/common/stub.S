#include "config.h"

#define EXPORT(name) \
.align 2; \
.section ".rplTramp.text","ax"; \
	.global name; \
	name: \
		li %r0, 0; \
		oris %r0, %r0, 0; \
		mtctr %r0; \
		bctr; \

#include "exports.h"
