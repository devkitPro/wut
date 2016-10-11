#include <malloc.h>
#include <string.h>
#include <coreinit/baseheap.h>
#include <coreinit/memheap.h>
#include <coreinit/expandedheap.h>

void *
__wrap_memalign(size_t alignment, size_t size) {
   return MEMAllocFromExpHeapEx(MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), size, alignment);
}

void *
__wrap_malloc(size_t size) {
   return __wrap_memalign(4, size);
}

void
__wrap_free(void *ptr) {
   if (ptr) {
      MEMFreeToExpHeap(MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), ptr);
   }
}

size_t
__wrap_malloc_usable_size(void *ptr) {
   return MEMGetSizeForMBlockExpHeap(ptr);
}

void *
__wrap_realloc(void *ptr, size_t size) {
   if (!ptr) {
      return __wrap_malloc(size);
   }

   if (__wrap_malloc_usable_size(ptr) >= size) {
      return ptr;
   }

   void *realloc_ptr = __wrap_malloc(size);

   if(!realloc_ptr) {
      return NULL;
   }

   memcpy(realloc_ptr, ptr, __wrap_malloc_usable_size(ptr));
   __wrap_free(ptr);

   return realloc_ptr;
}

void *
__wrap_calloc(size_t num, size_t size) {
   void *ptr = __wrap_malloc(num*size);

   if(ptr) {
      memset(ptr, 0, num*size);
   }

   return ptr;
}

void *
__wrap_valloc(size_t size) {
   return __wrap_memalign(64, size);
}



void *
__wrap__memalign_r(struct _reent *r, size_t alignment, size_t size) {
   return __wrap_memalign(alignment, size);
}

void *
__wrap__malloc_r(struct _reent *r, size_t size) {
   return __wrap_malloc(size);
}

void
__wrap__free_r(struct _reent *r, void *ptr) {
   return __wrap_free(ptr);
}

void *
__wrap__realloc_r(struct _reent *r, void *ptr, size_t size) {
   return __wrap_realloc(ptr, size);
}

void *
__wrap__calloc_r(struct _reent *r, size_t num, size_t size) {
   return __wrap_calloc(num, size);
}

size_t
__wrap__malloc_usable_size_r(struct _reent *r, void *ptr) {
   return __wrap_malloc_usable_size(ptr);
}

void *
__wrap__valloc_r(struct _reent *r, size_t size) {
   return __wrap_valloc(size);
}
