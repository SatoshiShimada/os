	.file	"main.c"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC0:
	.string	"Welcome to My OperatingSystem\n$ "
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"$ "
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	leal	-124(%ebp), %esi
	subl	$216, %esp
	movl	%esi, %edi
	call	init_idt
	call	init_pic
	call	init_pit
	subl	$12, %esp
	movl	$0, 16777216
	pushl	$1
	call	set_keytable
	movl	$0, keycode+32
	movl	$0, keycode+40
	movl	$0, keycode+36
	call	sti
	call	test_processor
	addl	$12, %esp
	pushl	$-1
	pushl	$4194304
	pushl	cpu
	call	memory_test
	movl	%eax, memory_total
	call	memory_control_init
	popl	%eax
	popl	%edx
	pushl	$647168
	pushl	$4096
	call	memory_free
	movl	memory_total, %eax
	popl	%ecx
	popl	%ebx
	subl	$4194304, %eax
	leal	-224(%ebp), %ebx
	pushl	%eax
	pushl	$4194304
	call	memory_free
	call	init_screen
	call	get_rootdir_file
	movl	$.LC0, (%esp)
	call	puts
	movl	$25, %ecx
	xorl	%eax, %eax
	addl	$16, %esp
	rep stosl
	.p2align 4,,10
	.p2align 3
.L2:
	call	hlt
	movl	$1374389535, %eax
	subl	$8, %esp
	mull	16777216
	shrl	$5, %edx
	pushl	%edx
	pushl	%ebx
	call	itoa
	addl	$12, %esp
	pushl	$0
	pushl	$77
	pushl	%ebx
	call	puts_position
	call	get_keycode_ascii
	movl	%eax, %edi
	movl	%ebx, (%esp)
	movb	%al, -224(%ebp)
	movb	$0, -223(%ebp)
	call	puts
	movl	%edi, %eax
	addl	$16, %esp
	cmpb	$10, %al
	je	.L7
	subl	$8, %esp
	pushl	%ebx
	pushl	%esi
	call	strcat
	addl	$16, %esp
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L7:
	subl	$12, %esp
	movl	%esi, %edi
	pushl	%esi
	call	do_command
	xorl	%eax, %eax
	movl	$25, %ecx
	rep stosl
	movl	$.LC1, (%esp)
	call	puts
	addl	$16, %esp
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.comm	memory_total,4,4
	.comm	keycode,48,32
	.ident	"GCC: (GNU) 4.9.2 20150304 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
