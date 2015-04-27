
.text
.globl load_eflags, store_eflags, cache_disable, cache_enable
.globl in_byte, out_byte
.globl sti, cli
.globl hlt

load_eflags:
	pushf
	pop		%eax
	#mov		4(%esp), %eax
	ret

store_eflags:
	mov		4(%esp), %eax
	push	%eax
	popf
	ret

cache_disable:
	mov		%cr0, %eax
	or		$0x60000000, %eax
	mov		%eax, %cr0
	ret

cache_enable:
	mov		%cr0, %eax
	and		$0x9fffffff, %eax
	mov		%eax, %cr0
	ret

in_byte: # int in_byte(int port);
	mov		4(%esp), %edx
	mov		$0, %eax
	in		%dx, %al
	ret

out_byte: # void out_byte(int port, int data);
	mov		4(%esp), %edx
	mov		8(%esp), %eax
	out		%al, %dx
	ret

sti:
	sti
	ret

cli:
	cli
	ret

hlt:
	hlt
	ret
