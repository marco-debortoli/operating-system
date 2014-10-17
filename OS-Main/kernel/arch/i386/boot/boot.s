# Declare constants used for creating a multiboot header
.set ALIGN,	1<<0		# align loaded modules on page boundaries
.set MEMINFO, 	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM, 	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
			
	call kernel_early

	call kernel_main

1: hlt
jmp 1b

.size _start, . - _start
