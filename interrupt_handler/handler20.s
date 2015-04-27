
.globl interrupt_handler20

# programmable interval timer
interrupt_handler20:
	pusha

	mov		$0x1000000, %esi
	add		$1, (%esi)

	mov		$0x20, %al
	out		%al, $0x20
	popa
	iret
