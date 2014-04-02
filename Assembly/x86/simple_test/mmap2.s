	.file	"mmap2.c"
	.section	.rodata
.LC0:
	.string	"%s file offset [length]\n"
.LC1:
	.string	"open"
.LC2:
	.string	"fstat"
.LC3:
	.string	"offset is past end of file\n"
.LC4:
	.string	"mmap"
.LC5:
	.string	"write"
.LC6:
	.string	"partial write"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	%edi, -196(%rbp)
	movq	%rsi, -208(%rbp)
	cmpl	$2, -196(%rbp)
	jle	.L2
	cmpl	$4, -196(%rbp)
	jle	.L3
.L2:
	movq	-208(%rbp), %rax
	movq	(%rax), %rdx
	movl	$.LC0, %ecx
	movq	stderr(%rip), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, %edi
	call	exit
.L3:
	movq	-208(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L4
	movl	$.LC1, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L4:
	leaq	-192(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fstat
	cmpl	$-1, %eax
	jne	.L5
	movl	$.LC2, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L5:
	movq	-208(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	cltq
	movq	%rax, -40(%rbp)
	movl	$30, %edi
	call	sysconf
	negq	%rax
	andq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-144(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jg	.L6
	movq	stderr(%rip), %rax
	movq	%rax, %rdx
	movl	$.LC3, %eax
	movq	%rdx, %rcx
	movl	$27, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite
	movl	$1, %edi
	call	exit
.L6:
	cmpl	$4, -196(%rbp)
	jne	.L7
	movq	-208(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	cltq
	movq	%rax, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdx
	addq	-48(%rbp), %rdx
	movq	-144(%rbp), %rax
	cmpq	%rax, %rdx
	jbe	.L8
	movq	-144(%rbp), %rax
	subq	-40(%rbp), %rax
	movq	%rax, -48(%rbp)
	jmp	.L8
.L7:
	movq	-144(%rbp), %rax
	subq	-40(%rbp), %rax
	movq	%rax, -48(%rbp)
.L8:
	movq	-40(%rbp), %rax
	movq	%rax, %rdx
	addq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	-32(%rbp), %rcx
	movl	-4(%rbp), %edx
	movq	%rcx, %r9
	movl	%edx, %r8d
	movl	$2, %ecx
	movl	$1, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	mmap
	movq	%rax, -24(%rbp)
	cmpq	$-1, -24(%rbp)
	jne	.L9
	movl	$.LC4, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L9:
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	addq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, %rsi
	movl	$1, %edi
	call	write
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	cmpq	-48(%rbp), %rax
	je	.L10
	cmpq	$-1, -16(%rbp)
	jne	.L11
	movl	$.LC5, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L11:
	movq	stderr(%rip), %rax
	movq	%rax, %rdx
	movl	$.LC6, %eax
	movq	%rdx, %rcx
	movl	$13, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite
	movl	$1, %edi
	call	exit
.L10:
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.4-1ubuntu1~12.04) 4.6.4"
	.section	.note.GNU-stack,"",@progbits
