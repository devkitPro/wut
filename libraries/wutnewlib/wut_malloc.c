#include <coreinit/memexpheap.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memorymap.h>
#include <malloc.h>
#include <string.h>

void *
_malloc_r(struct _reent *r, size_t size)
{
   return MEMAllocFromDefaultHeap(size);
}

void
_free_r(struct _reent *r, void *ptr)
{
   MEMFreeToDefaultHeap(ptr);
}

void *
_realloc_r(struct _reent *r, void *ptr, size_t size)
{
   void *new_ptr = _malloc_r(r, size);
   if (!ptr || !new_ptr) {
      return new_ptr;
   }

   memcpy(new_ptr, ptr, MEMGetSizeForMBlockExpHeap(ptr));
   _free_r(r, ptr);
   return new_ptr;
}

void *
_calloc_r(struct _reent *r, size_t num, size_t size)
{
   void *ptr = _malloc_r(r, num * size);
   if (ptr) {
      memset(ptr, 0, num * size);
   }

   return ptr;
}

void *
_memalign_r(struct _reent *r, size_t align, size_t size)
{
   return MEMAllocFromDefaultHeapEx(size, align);
}

struct mallinfo _mallinfo_r(struct _reent *r)
{
   struct mallinfo info = { 0 };
   return info;
}

void
_malloc_stats_r(struct _reent *r)
{
}

int
_mallopt_r(struct _reent *r, int param, int value)
{
   return 0;
}

size_t
_malloc_usable_size_r(struct _reent *r, void *ptr)
{
   return MEMGetSizeForMBlockExpHeap(ptr);
}

void *
_valloc_r(struct _reent *r, size_t size)
{
   return _memalign_r(r, OS_PAGE_SIZE, size);
}

void *
_pvalloc_r(struct _reent *r, size_t size)
{
   return _memalign_r(r, OS_PAGE_SIZE, (size + (OS_PAGE_SIZE - 1)) & ~(OS_PAGE_SIZE - 1));
}

int
_malloc_trim_r(struct _reent *r, size_t pad)
{
   return 0;
}
