.text

.globl after_MBR

.code16

after_MBR:
	mov		$0x13, %al
	mov		$0x00, %ah
	int		$0x10

real_to_protected:
	cli
	call	enable_a20_line
	cli
	xor		%ax, %ax
	mov		%ax, %ds
	DATA32 ADDR32 lgdt	gdtdesc

	mov		%cr0, %eax
	or		$0x01, %eax
	mov		%eax, %cr0

	# (8*2) is code segment
	DATA32	ljmp	$8*2, $protected_segment

.code32
protected_segment:
	# (8*1) is data segment
	mov		$8*1, %ax
	mov		%ax, %ds
	mov		%ax, %es
	mov		%ax, %fs
	mov		%ax, %gs
	mov		%ax, %ss

	mov		$0x81ff, %eax
	mov		%eax, %esp
	mov		%eax, %ebp

	lidt	protected_idt

	jmp		stage3

.align 8
gdtdesc:
	.word	8*3-1
	.long	gdt
.align 8
gdt:
	.word	0, 0
	.byte	0, 0, 0, 0
	# data segment
	.word	0xffff, 0x0000
	.byte	0x00, 0x92, 0xcf, 0x00
	# code segment
	.word	0xffff, 0x0000
	.byte	0x00, 0x9a, 0xcf, 0x00

.align 8
protected_idt:
	.word	0
	.long	0

# functions
enable_a20_line:
.code16
	cli

	call	a20_wait
	mov		$0xad, %al
	out		%al, $0x64
	call	a20_wait
	mov		$0xd0, %al
	out		%al, $0x64
	call	a20_wait2
	in		$0x60, %al
	push	%eax
	call	a20_wait
	mov		$0xd1, %al
	out		%al, $0x64
	call	a20_wait
	pop		%eax
	or		$0x02, %al
	out		%al, $0x60
	call	a20_wait
	mov		$0xae, %al
	out		%al, $0x64
	call	a20_wait
	
	sti
	ret

a20_wait:
	in		$0x64, %al
	test	$0x02, %al
	jnz		a20_wait
	ret

a20_wait2:
	in		$0x64, %al
	test	$0x01, %al
	jz		a20_wait2
	ret

.code32
stage3:
	# call to C program code
	call	main
endloop:
	jmp		endloop
