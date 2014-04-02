.include "linux_sys32.S"
.include "utility32.S"

.data
data:
	.int	1024
int_val:
	.int	0
.text
.global _start
_start:
	call	ABC
	movl	ABC, %eax
	pushl	%eax
	call	F_write_int

	movl	%eax, %ebx
	leal	data, %eax
	movl	data, %eax

	movl	$15, (%eax)

	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$0x80

ABC:
	movl	$100, %ebx
	ret

