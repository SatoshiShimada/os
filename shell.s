	.file	"shell.c"
	.section	.rodata
.LC0:
	.string	"memory"
.LC1:
	.string	"free"
.LC2:
	.string	"ls"
.LC3:
	.string	"hello"
.LC4:
	.string	"Hello! MyOS world\n"
.LC5:
	.string	"Unknown command\n"
	.text
	.globl	do_command
	.type	do_command, @function
do_command:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$.LC0
	pushl	8(%ebp)
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L2
	call	print_memory_size
	jmp	.L3
.L2:
	subl	$8, %esp
	pushl	$.LC1
	pushl	8(%ebp)
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L4
	call	print_memory_free
	jmp	.L3
.L4:
	subl	$8, %esp
	pushl	$.LC2
	pushl	8(%ebp)
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L5
	call	print_rootdir_file
	jmp	.L3
.L5:
	subl	$8, %esp
	pushl	$.LC3
	pushl	8(%ebp)
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L6
	subl	$12, %esp
	pushl	$.LC4
	call	puts
	addl	$16, %esp
	jmp	.L3
.L6:
	subl	$12, %esp
	pushl	$.LC5
	call	puts
	addl	$16, %esp
.L3:
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	do_command, .-do_command
	.section	.rodata
.LC6:
	.string	"memory: "
.LC7:
	.string	"MB\n"
	.text
	.globl	print_memory_size
	.type	print_memory_size, @function
print_memory_size:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$120, %esp
	subl	$12, %esp
	pushl	$.LC6
	call	puts
	addl	$16, %esp
	movl	memory_total, %eax
	shrl	$20, %eax
	subl	$8, %esp
	pushl	%eax
	leal	-108(%ebp), %eax
	pushl	%eax
	call	int_to_ascii
	addl	$16, %esp
	subl	$12, %esp
	leal	-108(%ebp), %eax
	pushl	%eax
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC7
	call	puts
	addl	$16, %esp
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	print_memory_size, .-print_memory_size
	.section	.rodata
.LC8:
	.string	"free: "
	.text
	.globl	print_memory_free
	.type	print_memory_free, @function
print_memory_free:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	subl	$116, %esp
	.cfi_offset 7, -12
	subl	$12, %esp
	pushl	$.LC8
	call	puts
	addl	$16, %esp
	call	get_memory_free_size
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leal	1023(%eax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$10, %eax
	subl	$8, %esp
	pushl	%eax
	leal	-112(%ebp), %eax
	pushl	%eax
	call	int_to_ascii
	addl	$16, %esp
	leal	-112(%ebp), %eax
	movl	$-1, %ecx
	movl	%eax, %edx
	movl	$0, %eax
	movl	%edx, %edi
	repnz scasb
	movl	%ecx, %eax
	notl	%eax
	leal	-1(%eax), %edx
	leal	-112(%ebp), %eax
	addl	%edx, %eax
	movl	$672331, (%eax)
	subl	$12, %esp
	leal	-112(%ebp), %eax
	pushl	%eax
	call	puts
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %edi
	leave
	.cfi_restore 5
	.cfi_restore 7
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	print_memory_free, .-print_memory_free
	.section	.rodata
.LC9:
	.string	"file: "
.LC10:
	.string	"\n"
.LC11:
	.string	""
	.string	""
	.text
	.globl	print_rootdir_file
	.type	print_rootdir_file, @function
print_rootdir_file:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$120, %esp
	movl	filecount, %eax
	subl	$8, %esp
	pushl	%eax
	leal	-116(%ebp), %eax
	pushl	%eax
	call	int_to_ascii
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC9
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	leal	-116(%ebp), %eax
	pushl	%eax
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC10
	call	puts
	addl	$16, %esp
	movl	$0, -12(%ebp)
	jmp	.L13
.L14:
	movl	-12(%ebp), %eax
	sall	$5, %eax
	addl	$file, %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	movl	%eax, -116(%ebp)
	movl	%edx, -112(%ebp)
	leal	-116(%ebp), %eax
	addl	$8, %eax
	movl	-12(%ebp), %edx
	sall	$5, %edx
	addl	$file, %edx
	addl	$8, %edx
	movzwl	(%edx), %ecx
	movw	%cx, (%eax)
	movzbl	2(%edx), %edx
	movb	%dl, 2(%eax)
	subl	$4, %esp
	pushl	$1
	pushl	$.LC11
	leal	-116(%ebp), %eax
	addl	$11, %eax
	pushl	%eax
	call	memcpy
	addl	$16, %esp
	subl	$12, %esp
	leal	-116(%ebp), %eax
	pushl	%eax
	call	puts
	addl	$16, %esp
	movl	$0, -16(%ebp)
	movl	-16(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	leal	-116(%ebp), %eax
	pushl	%eax
	call	int_to_ascii
	addl	$16, %esp
	subl	$12, %esp
	leal	-116(%ebp), %eax
	pushl	%eax
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC10
	call	puts
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L13:
	movl	filecount, %eax
	cmpl	%eax, -12(%ebp)
	jl	.L14
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	print_rootdir_file, .-print_rootdir_file
	.ident	"GCC: (GNU) 4.9.2 20150304 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
