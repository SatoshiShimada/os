
.globl interrupt_handler26

# keyboard
interrupt_handler26:
	pusha
	push	%ds
	push	%es
	mov		%ss, %ax
	mov		%ax, %ds
	mov		%ax, %es

	#call	function
	mov		$0xb8000, %esi
	movb	$'X', (%esi)
L0:	jmp		L0

	mov		$0x20, %al
	out		%al, $0x20

	pop		%es
	pop		%ds
	popa
	iret
