.text

.globl after_MBR

.code16

after_MBR:

# change screen mode
	mov		$0x11b + 0x4000, %bx
	mov		$0x4f02, %ax
	int		$0x10

	mov		$0x9000, %ax
	mov		%ax,%es
	mov		$0, %di
	mov		$0x11b, %cx
	mov		$0x4f01, %ax
	int		$0x10
	#mov		0x28(%es,%di), %eax
	#mov		0x28(,%es, 4), %eax
	#movl	40(%es), %eax
	#movl	40(%di, %es, 4), %eax
	mov		$0x9000, %di
	movl	0x28(%di), %eax
	mov		%eax, (0x1fff)


	mov		$msg, %si
print_msg:
	mov		(%si), %al
	cmp		$0, %al
	je		print_fin
	mov		$0x0e, %ah
	mov		$0x15, %bx
	int		$0x10
	add		$1, %si
	jmp		print_msg

print_fin:

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

	DATA32	ljmp	$8*1, $protected_segment

.code32
protected_segment:
	mov		$8*2, %ax
	mov		%ax, %ds
	mov		%ax, %es
	mov		%ax, %fs
	mov		%ax, %gs
	mov		%ax, %ss

	mov		$0x81ff, %eax
	mov		%eax, %esp
	mov		%eax, %ebp

	lidt	protected_idt

next_:
end:
	jmp		stage3

.align 8
gdtdesc:
	.word	8*3-1
	.long	gdt
.align 8
gdt:
	.word	0, 0
	.byte	0, 0, 0, 0
	# code segment
	.word	0xffff, 0x0000
	.byte	0x00, 0x9a, 0xcf, 0x00
	# data segment
	.word	0xffff, 0x0000
	.byte	0x00, 0x92, 0xcf, 0x00

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

.data
msg:
	.string	"loaded\r\n"

