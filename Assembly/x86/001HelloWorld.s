.include "linux_sys32.S"

.data
hello:
	.asciz "Hello World!\n"
	len = . - hello

printf_placeholder:
	.asciz "printf string: %s"

.text
.global _start
_start:
	pushl	%ebp
	movl	%esp, %ebp

	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$hello, %ecx
	movl	$len, %edx
	int		$0x80

	pushl	$hello
	pushl	$printf_placeholder
	call	printf
	addl	$8, %esp

	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$0x80

