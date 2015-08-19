
.text
.globl load_eflags, store_eflags, cache_disable, cache_enable
.globl in_byte, out_byte
.globl sti, cli
.globl hlt
.globl out_word
.globl cpuid_vendor_id, cpuid_processor_brand_string

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

cpuid_vendor_id:
	mov		$0, %eax
	cpuid
	movl	4(%esp), %edi
	movl	%ebx, (%edi)
	movl	%edx, 4(%edi)
	movl	%ecx, 8(%edi)
	ret

cpuid_processor_brand_string:
	movl	4(%esp), %edi
	movl	$0x80000000, %eax
	cpuid
	cmpl	$0x80000004, %eax
	jl		no_support_function
	movl	$0x80000002, %eax
	cpuid
	movl	%eax, 0(%edi)
	movl	%ebx, 4(%edi)
	movl	%ecx, 8(%edi)
	movl	%edx, 12(%edi)
	movl	$0x80000003, %eax
	cpuid
	movl	%eax, 16(%edi)
	movl	%ebx, 20(%edi)
	movl	%ecx, 24(%edi)
	movl	%edx, 28(%edi)
	movl	$0x80000004, %eax
	cpuid
	movl	%eax, 32(%edi)
	movl	%ebx, 36(%edi)
	movl	%ecx, 40(%edi)
	movl	%edx, 44(%edi)
	ret
no_support_function:
	movl	$0x00, 0(%edi)
	ret
