.file		"macro32.S"

.include	"linux_sys32.S"

# MACRO
.section .bss

.macro M_write	string, string_len
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	\string, %ecx
	movl	\string_len, %edx
	int		$LINUX_SYS_CALL
.endm # M_write

.macro M_read	buffer, buffer_len
	movl	$sys_read, %eax
	movl	$STDIN_FILENO, %ebx
	movl	\buffer, %ecx
	movl	\buffer_len, %edx
	int		$LINUX_SYS_CALL
.endm # M_read

# MACRO END

