.file "utility32.S"

.include "linux_sys32.S"

/* ----function list----
F_writeln
F_write_int
F_compare_char
F_compare_int
*/

# RODATA
.section .rodata

.local	endline
.local	endline_len
				endline:
.ascii			"\n"
				endline_len =				. - endline

# RODATA END

# BSS
.section .bss

.local	buffer
.local	buffer_len
				buffer_len =				1024
.lcomm			buffer,						buffer_len
				buffer_act_len:				.int	0

# BSS END

.section .text

/**
 * @brief	print an endline ===> putchar('\n')
 * @input	F_writeln()
 */
.type F_writeln, @function
.global F_writeln
F_writeln:
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$endline, %ecx
	movl	$endline_len, %edx
	int		$LINUX_SYS_CALL
	ret

/**
 * @brief	write an int into STDOUT_FILENO
 * @input	void F_write_int(int)
 */
.type F_write_int, @function
.global	F_write_int
F_write_int:
	movl	4(%esp), %eax				# get length of the number
	cmpl	$0, %eax					# number < 0?
	jge		positive_number
	neg		%eax
	movl	%eax, 4(%esp)
	movl	$1, %ebx
	movl	$45, buffer					# '-' ==> 45
	movl	$10, %ecx
	jmp		counting_size
.local	positive_number
positive_number:
	xorl	%ebx, %ebx
	movl	$10, %ecx
.local	counting_size
counting_size:
	xor		%edx, %edx
	idiv	%ecx
	inc		%ebx
	cmpl	$0, %eax
	jnz		counting_size

	movl	4(%esp), %eax
	movl	%ebx, buffer_act_len
	dec		%ebx
.local	to_string
to_string:
	xor		%edx, %edx
	idiv	%ecx
	addl	$48, %edx					# %edx = number%10 + '0'
	movb	%dl, buffer(, %ebx, 1)
	dec		%ebx
	cmpl	$0, %eax
	jnz		to_string
	
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$buffer, %ecx
	movl	buffer_act_len, %edx
	int		$LINUX_SYS_CALL

	ret		$4

/**
 * @brief	Compare 2 ints
 * @input	int F_compare_int(const void * first, const void * second)
 * @output	return (*first)-(*second)
 */
.type F_compare_int, @function
.global F_compare_int
F_compare_int:
	movl	4(%esp), %eax
	movl	8(%esp), %ecx
	movl	(%eax), %eax
	movl	(%ecx), %ecx
	subl	%ecx, %eax
	ret		$8

/**
 * @brief	Compare 2 char
 * @input	int F_compare_char(const void * first, const void * second)
 * @output	return (*first)-(*second)
 */
.type F_compare_char, @function
.global F_compare_char
F_compare_char:
	movl	4(%esp), %eax
	movl	8(%esp), %ecx
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movzbl	(%ecx), %ecx
	movsbl	%cl, %ecx
	subl	%ecx, %eax
	ret		$8

