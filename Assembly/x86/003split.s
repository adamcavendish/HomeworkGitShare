.include "linux_sys32.S"

# RODATA
.section .rodata
			input_prompt:
.ascii		"Please Input A String:\n"
			input_prompt_len =				. - input_prompt
			
			reinput_prompt:
.ascii		"Error, Please Reinput A String:\n"
			reinput_prompt_len =			. - reinput_prompt

			maxlen_exceed_prompt:
.ascii		"Exceeds max length. Program Exit\n"
			maxlen_exceed_prompt_len =		. - maxlen_exceed_prompt

			number_prompt:
.ascii		"Numbers are: "
			number_prompt_len =				. - number_prompt

			char_prompt:
.ascii		"Letters are: "
			char_prompt_len =				. - char_prompt

			endline:
.ascii		"\n"
			endline_len =					. - endline

# RODATA END

# DATA SECTION
.section .data
			string_data_max_len =			1024
.lcomm		string_data,					string_data_max_len
			string_data_act_len:			.int	0

			num_data_max_len =				string_data_max_len
.lcomm		num_data,						num_data_max_len
			num_data_act_len:				.int	0

			char_data_max_len =				string_data_max_len
.lcomm		char_data,						char_data_max_len
			char_data_act_len:				.int	0
# DATA SECTION END

# BSS SECTION
.section .bss
			buffer_len =					10000
.lcomm		buffer,							buffer_len
# BSS SECTION END

# DATA SECTION END

.section .text
.global _start
_start:
	# Print the Prompt
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$input_prompt, %ecx
	movl	$input_prompt_len, %edx
	int		$LINUX_SYS_CALL

_start__read:
	# Read the string
	movl	$sys_read, %eax
	movl	$STDIN_FILENO, %ebx
	movl	$string_data, %ecx
	movl	$string_data_max_len, %edx
	int		$LINUX_SYS_CALL
	# Get actual string length
	cmpl	$-1, %eax
	je		_start__reinput
	cmpl	$0, %eax
	je		_start__reinput
	cmpl	$1, %eax						# You can't just type ENTER
	je		_start__reinput
	cmpl	$string_data_max_len, %eax		# don't go beyond max len
	jne		_start__L0
	# maxlen exceeded Prompt
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$maxlen_exceed_prompt, %ecx
	movl	$maxlen_exceed_prompt_len, %edx
	int		$LINUX_SYS_CALL
	jmp		_start__exit
	# Reinput Prompt
_start__reinput:
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$reinput_prompt, %ecx
	movl	$reinput_prompt_len, %edx
	int		$LINUX_SYS_CALL
	jmp		_start__read
_start__L0:
	# cut off the endline
	subl	$endline_len, %eax
	movl	%eax, string_data_act_len
# --------------------------------------------------
	# for every char check
	xor		%ecx, %ecx
	xor		%edi, %edi
	xor		%edx, %edx
	movl	string_data_act_len, %ecx
	movl	char_data_act_len, %edi
	movl	num_data_act_len, %edx
_start__L1:
	movl	string_data_act_len, %ebx
	subl	%ecx, %ebx
	movb	string_data(, %ebx, 1), %al
	call	F_check_char_or_num
	# ==(1 | 2), a capital letter or a non-capitcal letter?
	test	$3, %ebx
	jz		_start__check_every_char__check_num
	movl	%eax, char_data(, %edi, 1)
	inc		%edi
	jmp		_start__check_every_char__neither
_start__check_every_char__check_num:
	# == 4, a number?
	cmpl	$4, %ebx
	jne		_start__check_every_char__neither
	movl	%eax, num_data(, %edx, 1)
	inc		%edx
_start__check_every_char__neither:
	loop	_start__L1
	# after loop write back
	movl	%edi, char_data_act_len
	movl	%edx, num_data_act_len

# --------------------------------------------------

	# print out chars and nums

	# Print the chars
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$char_prompt, %ecx
	movl	$char_prompt_len, %edx
	int		$LINUX_SYS_CALL

	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$char_data, %ecx
	movl	char_data_act_len, %edx
	int		$LINUX_SYS_CALL

	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$endline, %ecx
	movl	$endline_len, %edx
	int		$LINUX_SYS_CALL

	# Print the nums
	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$number_prompt, %ecx
	movl	$number_prompt_len, %edx
	int		$LINUX_SYS_CALL

	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$num_data, %ecx
	movl	num_data_act_len, %edx
	int		$LINUX_SYS_CALL

	movl	$sys_write, %eax
	movl	$STDOUT_FILENO, %ebx
	movl	$endline, %ecx
	movl	$endline_len, %edx
	int		$LINUX_SYS_CALL

	# Exit
_start__exit:
	movl	$sys_exit, %eax
	xor		%ebx, %ebx
	int		$LINUX_SYS_CALL

/**
 * @input	%eax -- byte character, using only %al to check
 * @output	%ebx
 *			-- return 0: not a char && not a number, eg: '%'
 *			-- return 1: a capital char, eg: 'A'
 *			-- return 2: a non-captital char, eg: 'a'
 *			-- return 4: a number, eg: '1'
 */
.type	F_check_char_or_num, @function
F_check_char_or_num:
	cmpb	$48, %al			# '0' is 48
	jb		F_check_char_or_num__not_char_not_num
	cmpb	$57, %al			# '9' is 57
	jbe		F_check_char_or_num__a_number
	cmpb	$65, %al			# 'A' is 65
	jb		F_check_char_or_num__not_char_not_num
	cmpb	$90, %al			# 'Z' is 90
	jbe		F_check_char_or_num__a_capitcal_char
	cmpb	$97, %al			# 'a' is 97
	jb		F_check_char_or_num__not_char_not_num
	cmpb	$122, %al			# 'z' is 122
	jbe		F_check_char_or_num__a_non_capital_char
F_check_char_or_num__not_char_not_num:
	movl	$0, %ebx
	ret
F_check_char_or_num__a_capitcal_char:
	movl	$1, %ebx
	ret
F_check_char_or_num__a_non_capital_char:
	movl	$2, %ebx
	ret
F_check_char_or_num__a_number:
	movl	$4, %ebx
	ret

