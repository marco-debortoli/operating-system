/*

	Implementation for heap
	Base Class: arch/i386/heap.c

*/

#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <stdio.h>
#include <stdint.h>
#include <kernel/ordered_map.h>

// --- Kernel memory allocation functions --- //

/**
   Allocate a chunk of memory, sz in size. If align == 1,
   the chunk must be page-aligned. If phys != 0, the physical
   location of the allocated chunk will be stored into phys.

   This is the internal version of kmalloc. More user-friendly
   parameter representations are available in kmalloc, kmalloc_a,
   kmalloc_ap, kmalloc_p.
**/
uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);

/**
   Allocate a chunk of memory, sz in size. The chunk must be
   page aligned.
**/
uint32_t kmalloc_a(uint32_t sz);

/**
   Allocate a chunk of memory, sz in size. The physical address
   is returned in phys. Phys MUST be a valid pointer to uint32_t!
**/
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);

/**
   Allocate a chunk of memory, sz in size. The physical address 
   is returned in phys. It must be page-aligned.
**/
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);

/**
   General allocation function.
**/
uint32_t kmalloc(uint32_t sz);

/**
   General deallocation function.
**/
void kfree(void *p);

// --- Other Heap functions --- //

#define HEAP_START		0xC0000000
#define HEAP_INITIAL_SIZE	0x100000
#define HEAP_INDEX_SIZE		0x20000
#define HEAP_MAGIC		0x123890AB
#define HEAP_MIN_SIZE		0x70000

typedef struct
{
	uint32_t magic; // The magic number defined above
	uint8_t is_hole; // 1 if it is a hole, 0 otherwise (end of block)
	uint32_t size;
} header_t;

typedef struct
{
	uint32_t magic;
	header_t *header;
} footer_t;

typedef struct
{
	ordered_map_t index;
	uint32_t start_address; // Start of allocated space
	uint32_t end_address; // End of allocated space, up to max_address
	uint32_t max_address; // The maximum address the heap can exapnd to
	uint8_t supervisor; // Supervisor only?
	uint8_t readonly; // Read only?
} heap_t;

heap_t* create_heap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readonly);

// Allocates a contiguous region of memory. If page_align==1, it creates that block starting at page boundary
void* alloc(uint32_t size, uint8_t page_align, heap_t* heap);

// Releases a block allocated with alloc
void free(void* p, heap_t* heap);


#endif  
