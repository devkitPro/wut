/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include <malloc.h>
#include <string.h>
#include <coreinit/baseheap.h>
#include <coreinit/frameheap.h>
#include <coreinit/expandedheap.h>
#include "memory.h"

#define MEMORY_ARENA_1          0
#define MEMORY_ARENA_2          1
#define MEMORY_ARENA_3          2
#define MEMORY_ARENA_4          3
#define MEMORY_ARENA_5          4
#define MEMORY_ARENA_6          5
#define MEMORY_ARENA_7          6
#define MEMORY_ARENA_8          7
#define MEMORY_ARENA_FG_BUCKET  8

static void *mem1_heap;
static void *bucket_heap;

void memoryInitialize(void)
{
    void *mem1_heap_handle = MEMGetBaseHeapHandle(MEMORY_ARENA_1);
    unsigned int mem1_allocatable_size = MEMGetAllocatableSizeForFrmHeapEx(mem1_heap_handle, 4);
    void *mem1_memory = MEMAllocFromFrmHeapEx(mem1_heap_handle, mem1_allocatable_size, 4);
    if(mem1_memory)
        mem1_heap = MEMCreateExpHeapEx(mem1_memory, mem1_allocatable_size, 0);

    void *bucket_heap_handle = MEMGetBaseHeapHandle(MEMORY_ARENA_FG_BUCKET);
    unsigned int bucket_allocatable_size = MEMGetAllocatableSizeForFrmHeapEx(bucket_heap_handle, 4);
    void *bucket_memory = MEMAllocFromFrmHeapEx(bucket_heap_handle, bucket_allocatable_size, 4);
    if(bucket_memory)
        bucket_heap = MEMCreateExpHeapEx(bucket_memory, bucket_allocatable_size, 0);
}

void memoryRelease(void)
{
    MEMDestroyExpHeap(mem1_heap);
    MEMFreeToFrmHeap(MEMGetBaseHeapHandle(MEMORY_ARENA_1), 3);
    mem1_heap = NULL;

    MEMDestroyExpHeap(bucket_heap);
    MEMFreeToFrmHeap(MEMGetBaseHeapHandle(MEMORY_ARENA_FG_BUCKET), 3);
    bucket_heap = NULL;
}

//!-------------------------------------------------------------------------------------------
//! some wrappers
//!-------------------------------------------------------------------------------------------
void * MEM2_alloc(unsigned int size, unsigned int align)
{
    return memalign(align, size);
}

void MEM2_free(void *ptr)
{
    free(ptr);
}

void * MEM1_alloc(unsigned int size, unsigned int align)
{
    if (align < 4)
        align = 4;
    return MEMAllocFromExpHeapEx(mem1_heap, size, align);
}

void MEM1_free(void *ptr)
{
    MEMFreeToExpHeap(mem1_heap, ptr);
}

void * MEMBucket_alloc(unsigned int size, unsigned int align)
{
    if (align < 4)
        align = 4;
    return MEMAllocFromExpHeapEx(bucket_heap, size, align);
}

void MEMBucket_free(void *ptr)
{
    MEMFreeToExpHeap(bucket_heap, ptr);
}
