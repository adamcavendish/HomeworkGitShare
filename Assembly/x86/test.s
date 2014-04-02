.include "linux_sys32.S"
.include "utility32.S"

.data

.text
.global _start
_start:
	movl	%eax, ABC
	pushl	%eax
	call	F_write_int

	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$0x80

ABC:
	movl	%ebx, 100
	ret

