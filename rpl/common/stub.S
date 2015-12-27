#include "config.h"

#define EXPORT(name) \
.align 2; \
.section ".rplTramp.text","ax"; \
	.global name; \
	name: \
		li %r0, name##_stub@l; \
		oris %r0, %r0, name##_stub@ha; \
		mtctr %r0; \
		bctr; \

#include "exports.h"
