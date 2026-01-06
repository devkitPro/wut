#include <coreinit/memdefaultheap.h>

void
__init_wut_sbrk_heap(MEMHeapHandle heapHandle);
void
__init_wut_thread();
void
__init_wut_defaultheap();

void __attribute__((weak))
__preinit_user(MEMHeapHandle *mem1,
               MEMHeapHandle *foreground,
               MEMHeapHandle *mem2)
{
   __init_wut_sbrk_heap(*mem2);
   __init_wut_thread();
   __init_wut_defaultheap();
}
