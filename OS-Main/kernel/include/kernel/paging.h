/*

	Paging implementation
	Base Class: arch/i386/paging/paging.c

*/

#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdio.h>
#include <stdint.h>
#include <kernel/portio.h>

typedef struct page
{
	uint32_t present	: 1; // Page present in memory
	uint32_t rw		: 1; // Read-only
	uint32_t user		: 1; // Supervisor level only
	uint32_t accessed	: 1; // Has the page been accessed since last refresh?
	uint32_t dirty		: 1; // Has the page been written to since last refresh?
	uint32_t unused		: 7; // Amalgmation of unused and reserved bits
	uint32_t frame		: 20; // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	// Array of pointers to page tables
	page_table_t *tables[1024];

	// Array of pointers to the page tables above
	// Physical location, for loading into the CR3 register
	uint32_t tablesPhysical[1024];

	// The physical address of tablesPhysical
	uint32_t physicalAddr;
} page_directory_t;


// Sets up the environment, page directories etc and
// enables paging.
void initialize_paging();

// Causes the specified page directory to be loaded into the CR3 register
void switch_page_directory(page_directory_t *new);

// Retrieves a pointer to the page
page_t *get_page(uint32_t address, int make, page_directory_t *dir);

// Handler for page faults
void page_fault(struct regs *r);

#endif
