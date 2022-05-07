#include <coreinit/memdefaultheap.h>
#include <malloc.h>

void *
__wut_alloc_from_defaultheap(uint32_t size)
{
   return malloc(size);
}

void *
__wut_alloc_from_defaultheap_ex(uint32_t size, 
                              int32_t alignment)
{
   return memalign(alignment, size);
}

void 
__wut_free_to_defaultheap(void *ptr)
{
   free(ptr);
}

void
__init_wut_defaultheap(void)
{
   MEMAllocFromDefaultHeap = __wut_alloc_from_defaultheap;
   MEMAllocFromDefaultHeapEx = __wut_alloc_from_defaultheap_ex;
   MEMFreeToDefaultHeap = __wut_free_to_defaultheap;
}

void
__fini_wut_defaultheap(void)
{
}
