
.text
.globl load_eflags, store_eflags, cache_disable, cache_enable
.globl in_byte, out_byte
.globl out_word
.globl sti, cli
.globl hlt, sti_hlt
.globl load_gdtr, load_idtr

load_eflags:
	pushf
	pop		%eax
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

out_word: # void out_word(int port, int data);
	mov		4(%esp), %edx
	mov		8(%esp), %eax
	out		%ax, %dx
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

sti_hlt:
	sti
	hlt
	ret

load_gdtr: # void load_gdtr(int limit, int addr);
	mov		4(%esp), %ax
	mov		%ax, 6(%esp)
	lgdt	6(%esp)
	ret

load_idtr:
	mov		4(%esp), %ax
	mov		%ax, 6(%esp)
	lidt	6(%esp)
	ret

