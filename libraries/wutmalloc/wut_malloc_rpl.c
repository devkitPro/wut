#include <coreinit/memexpheap.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memorymap.h>
#include <coreinit/debug.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/**
 * A special version of wutmalloc for RPLs.
 * 
 * RPLs can't reliable assume that the main application is using ExpHeap,
 * which means that MEMGetSizeForMBlockExpHeap can't be used for realloc.
 * This version co-allocates a header alongside the memory to be able to
 * reallocate the memory.
 */
void
__init_wut_malloc_rpl(void)
{
}

void
__fini_wut_malloc_rpl(void)
{
}

#define WUT_MALLOC_RPL_CANARY (0x376296a9)

struct wut_alloc_header_rpl
{
   uint32_t canary;
   size_t size;
   size_t offset;
};

static struct wut_alloc_header_rpl *get_alloc_header(const void* ptr)
{
   struct wut_alloc_header_rpl *header = (struct wut_alloc_header_rpl*)ptr - 1;
   assert(header->canary == WUT_MALLOC_RPL_CANARY);
   if(header->canary != WUT_MALLOC_RPL_CANARY)
      OSFatal("WUT detected a memory corruption in get_alloc_header");
   return header;
}

static void *get_alloc_base(struct wut_alloc_header_rpl* header)
{
   return (char*)header - header->offset;
}

void *
_malloc_r(struct _reent *r, size_t size)
{
	return _memalign_r(r, 0x40, size);
}

void
_free_r(struct _reent *r, void *ptr)
{
   if (ptr) {
      void *basePtr = get_alloc_base(get_alloc_header(ptr));
      MEMFreeToDefaultHeap(basePtr);
   }
}

void *
_realloc_r(struct _reent *r, void *ptr, size_t size)
{
   void *new_ptr = _malloc_r(r, size);
   if (!new_ptr) {
      r->_errno = ENOMEM;
      return new_ptr;
   }

   if (ptr) {
      struct wut_alloc_header_rpl *header = get_alloc_header(ptr);
      size_t old_size = header->size;
      memcpy(new_ptr, ptr, old_size <= size ? old_size : size);
      MEMFreeToDefaultHeap(get_alloc_base(header));
   }
   return new_ptr;
}

void *
_calloc_r(struct _reent *r, size_t num, size_t size)
{
   void *ptr = _malloc_r(r, num * size);
   if (ptr) {
      memset(ptr, 0, num * size);
   } else {
      r->_errno = ENOMEM;
   }
   return ptr;
}

void *
_memalign_r(struct _reent *r, size_t align, size_t size)
{
    if(align < 0x40)
        align = 0x40;
   size_t offset;
   void* basePtr;
   if(sizeof(struct wut_alloc_header_rpl) > align)
      offset = align - (sizeof(struct wut_alloc_header_rpl) % align);
   else
      offset = align - sizeof(struct wut_alloc_header_rpl);
   basePtr = MEMAllocFromDefaultHeapEx(offset + sizeof(struct wut_alloc_header_rpl) + size, align);
   if (!basePtr) {
      r->_errno = ENOMEM;
      return basePtr;
   }
   struct wut_alloc_header_rpl *header = (struct wut_alloc_header_rpl*)((char*)basePtr + offset);
   header->canary = WUT_MALLOC_RPL_CANARY;
   header->size = size;
   header->offset = offset;
   return (header+1);
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
   return 0; // we do not know the total available size
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