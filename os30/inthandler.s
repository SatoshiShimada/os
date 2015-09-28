
.globl asm_inthandler21 # for PS/2 keyboard
.globl asm_inthandler2c # for PS/2 mouse

.extern inthandler21
.extern inthandler2c

asm_inthandler21:
	push	%es
	push	%ds
	pusha
	mov		%esp, %eax
	push	%eax
	mov		%ss, %ax
	mov		%ax, %ds
	mov		%ax, %es

	xor		%eax, %eax
	inb		$0x60, %al
	push	%eax
	call	inthandler21
	pop		%eax

	mov		$0x20, %al
	out		%al, $0x20

	pop		%eax
	popa
	pop		%ds
	pop		%es
	iret

asm_inthandler2c:
	iret
