#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/paging.h>
#include <kernel/heap.h>
#include <kernel/portio.h>
#include <kernel/isr.h>
#include <kernel/panic.h>

// IMPORTANT NOTE 0x1000 is 4MB

// The kernel's page directory
page_directory_t* kernel_directory = 0;

// The current page directory
page_directory_t* current_directory = 0;

// A bitset of frames - used or free
uint32_t* frames;
uint32_t nFrames;

// Defined in heap.c
extern uint32_t placement_address;
extern heap_t *kheap;

#define INDEX_FROM_BIT(a) ( a / (8*4) )
#define OFFSET_FROM_BIT(a) ( a % (8*4) )

// Static function to set a bit in the frames bitset
static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t ofst = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << ofst);
}

// Static function to clear a bit in the bitset
static void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t ofst = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << ofst);
}

// Static function to test bit setting
static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t ofst = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << ofst));
}

// Find the first free frame
static uint32_t first_frame()
{
	for (uint32_t i = 0; i < INDEX_FROM_BIT(nFrames); i++)
	{
		if (frames[i] != 0xFFFFFFFF) // Last frame used
		{
			// At least one bit is free
			for ( uint32_t j = 0; j < 32; j++ )
			{
				uint32_t toTest = 0x1 << j;
				if ( !(frames[i]&toTest) ) return i*4*8 + j;
			}
		}
	}

	return 0;
}

// Allocate a frame
void alloc_frame(page_t* page, int is_kernel, int is_writeable)
{
	if ( page->frame != 0 )
	{
		return;
	}
	else
	{
		uint32_t idx = first_frame();
		if ( idx == (uint32_t)-1 )
		{
			// PANIC
			PANIC("Ran out of memory");
		}
		
		set_frame(idx*0x1000);
		page->present = 1;
		page->rw = (is_writeable) ? 1 : 0;
		page->user = (is_kernel) ? 0 : 1;
		page->frame = idx;
	}
}

void free_frame(page_t* page)
{
	uint32_t frame;
	if ( !(frame=page->frame) )
		return;

	else
	{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

void initialize_paging()
{
	// The size of physical memory (assume 16MB)
	uint32_t mem_end_page = 0x1000000;

	nFrames = mem_end_page / 0x1000;

	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nFrames));
	memset(frames, 0, INDEX_FROM_BIT(nFrames));

	// Make a page directory
	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	// Map some pages in the kernel heap area.
	// Here we call get_page but not alloc_frame. This causes page_table_t's 
	// to be created where necessary. We can't allocate frames yet because they
	// they need to be identity mapped first below, and yet we can't increase
	// placement_address between identity mapping and enabling the heap!
	
	int i = 0;
	
	for (i = HEAP_START; i < HEAP_START + HEAP_INITIAL_SIZE; i += 0x1000)
		get_page(i, 1, kernel_directory);

	i = 0;

	// Map virt -> phys
	// Need to add 0x1000 so that the kernel heap can initialize properly
	while ( i < placement_address + 0x1000)
	{
		// Kernel code is readable but NOT writeable
		alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}

	// Now allocate those pages we mapped earlier
	for ( i = HEAP_START; i < HEAP_START + HEAP_INITIAL_SIZE; i += 0x1000 )
		alloc_frame ( get_page ( i , 1, kernel_directory), 0, 0);


	// Before we enable paging we mus register our page fault handler
	register_interrupt_handler(14, page_fault);

	switch_page_directory(kernel_directory);

	// Initialise the kernel heap.
	kheap = create_heap(HEAP_START, HEAP_START + HEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
	
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;

	//printf("DIR: > 0x%i" , (int)&current_directory->tablesPhysical);
	//for(;;); 

	asm volatile("mov %0, %%cr3":: "b"(&dir->tablesPhysical));


	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	
	cr0 |= 0x80000000; // Enable paging!
	
	asm volatile("mov %0, %%cr0":: "b"(cr0));


}

page_t *get_page(uint32_t address, int make, page_directory_t* dir)
{
	// Turn the address into an index
	address /= 0x1000;

	uint32_t table_idx = address / 1024;
	if ( dir->tables[table_idx] ) // already assigned
	{
		return &dir->tables[table_idx]->pages[address % 1024];	
	}

	else if(make) // Create the page
	{
		uint32_t tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
		dir->tablesPhysical[table_idx] = tmp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else 
	{
		return 0;
	}
}

void page_fault(struct regs *r)
{
	// Page fault handler
	uint32_t faulting_address = 0x0;
	asm volatile ("mov %%cr2, %0" : "=r" (faulting_address));

	// The error code gives us details of what happened.
	int present   = !(r->err_code & 0x1); // Page not present
	int rw = r->err_code & 0x2;           // Write operation?
	int us = r->err_code & 0x4;           // Processor was in user-mode?
	int reserved = r->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?

	printf("Page fault! ( ");
	if ( present ) printf("present ");
	if ( rw ) printf("read-only ");
	if ( us ) printf("user-mode ");
	if ( reserved ) printf("reserved ");
	printf(" ) at 0x");


	printf("%x\n", (unsigned int)(faulting_address));

	PANIC("Paging Fault Panic");
}
