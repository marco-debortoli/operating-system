.global gdt_flush

gdt_flush:
	movl 4(%esp), %eax
	lgdt (%eax)		// Load the new GDT pointer

	movw %ax, 0x10		// 0x10 is the offest in the GDT
	movw %ds, %ax		
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movw %ss, %ax
	jmp $0x08, $flush		// 0x08 is the offset to the code segment

flush:
	ret

.global idt_flush

idt_flush:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
