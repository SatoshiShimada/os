
.globl interrupt_handler21
# void key_encoder(int keycode);
.extern key_encoder

# keyboard
interrupt_handler21:
	pusha
	push	%ds
	push	%es
	mov		%ss, %ax
	mov		%ax, %ds
	mov		%ax, %es

	xor		%eax, %eax
	inb		$0x60, %al
	push	%eax
	call	key_encoder
	pop		%eax

	mov		$0x20, %al
	out		%al, $0x20

	pop		%es
	pop		%ds
	popa
	iret
