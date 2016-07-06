#include "config.h"

#define EXPORT(name) \
.align 2; \
.section ".rplTramp.text","ax"; \
   .global name; \
   name: \
      lis %r0, name##_stub@h; \
      ori %r0, %r0, name##_stub@l; \
      mtctr %r0; \
      bctr;

#include "exports.h"
