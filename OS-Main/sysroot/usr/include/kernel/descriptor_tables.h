/*

	Defines the interface for initialising GDT and IDT

*/

#include <stddef.h>
#include <stdint.h>

#include <kernel/portio.h>

// Initialization function 
void init_descriptor_tables();

// This struct contains the value for one GDT entry
struct gdt_entry_struct
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)); // Tell GCC not to change the alignment

typedef struct gdt_entry_struct gdt_entry_t;

// This struct describes a GDT Pointer
// It points to the start of the array
struct gdt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// A struct describing an interrupt gate
struct idt_entry_struct
{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to the IDT array
struct idt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// These extern directives access the ASM ISR handlers
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10 ();
extern void isr11 ();
extern void isr12 ();
extern void isr13 ();
extern void isr14 ();
extern void isr15 ();
extern void isr16 ();
extern void isr17 ();
extern void isr18 ();
extern void isr19 ();
extern void isr20 ();
extern void isr21 ();
extern void isr22 ();
extern void isr23 ();
extern void isr24 ();
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 ();

