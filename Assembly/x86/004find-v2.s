.include "linux_sys32.S"
.include "macro32.S"

# RODATA
.section .rodata
				input_prompt: 
.ascii			"Please Input A String:\n"
				input_prompt_len =			. - input_prompt

				sorted_prompt:
.ascii			"Sorted Data: \n"
				sorted_prompt_len =			. - sorted_prompt

				search_prompt:
.ascii			"Please Input A Char For Search:\n"
				search_prompt_len =			. - search_prompt

				reinput_prompt:
.ascii			"We need only one character. Please Reinput:\n"
				reinput_prompt_len =		. - reinput_prompt

				not_found_prompt:
.ascii			"No Key Was Found!\n"
				not_found_prompt_len =		. - not_found_prompt
				
				found_targets_prompt:
.ascii			"Found targets number: "
				found_targets_prompt_len =	. - found_targets_prompt
# RODATA END

# DATA SECTION
.section .data
				string_data_len =			1024
.lcomm			string_data,				string_data_len
				string_data_act_len:		.int	0

				counter:					.int	0
				position:					.int	0

# DATA SECTION END

# BSS SECTION
.section .bss
				buffer_len =				1024
.lcomm			buffer,						buffer_len
				buffer_act_len:				.int	0
# BSS SECTION END

.section .text
.global _start
_start:
	pushl	%ebp
	movl	%esp, %ebp
	# print input_prompt
	M_write $input_prompt, $input_prompt_len

	# read a string
	M_read	$string_data, $string_data_len
	dec		%eax							# cutoff the endline
	movl	%eax, string_data_act_len

	# insersion_sort string_data
	pushl	$F_compare_char					# @PUT_PARAM 4th
	pushl	$1	# sizeof(char)				# @PUT_PARAM 3rd
	pushl	string_data_act_len				# @PUT_PARAM 2nd
	pushl	$string_data					# @PUT_PARAM 1st
	call	F_insertion_sort32

	# print sorted_prompt
	M_write	$sorted_prompt, $sorted_prompt_len

	# print string_data
	M_write	$string_data, string_data_act_len

	# print endline
	call	F_writeln

	# print search char input prompt
	M_write	$search_prompt, $search_prompt_len

_start__L0:
	# read searching character
	M_read	$buffer, $buffer_len
	cmpl	$2, %eax
	je		_start__searching

	M_write	$reinput_prompt, $reinput_prompt_len
	jmp		_start__L0

_start__searching:
	xorl	%eax, %eax
	movl	%eax, counter					# counter = 0

	pushl	$F_compare_char					# @PUT_PARAM 5th, compare_function
	pushl	$1								# @PUT_PARAM 4th, sizeof(array[0])
	pushl	string_data_act_len				# @PUT_PARAM 3rd, @GET_PARAM array_len
	pushl	$string_data					# @PUT_PARAM 2nd, @GET_PARAM array
	leal	buffer, %eax
	pushl	%eax							# @PUT_PARAM 1st, key
	call	F_bsearch32
	cmpl	$0, %eax						# return NULL?
	je		_start__not_found
	subl	$string_data, %eax
	movl	%eax, position					# save the bsearch found position
	movl	%eax, %ecx						# %ecx = position
	movzbl	buffer, %esi					# %edi = key

	movl	counter, %edx					# %edx = counter
	inc		%edx

	cmpl	$0, %ecx						# alias data <- array[pos] 
	je		_start__search_right
_start__search_left:						# search left, until data != key
	cmpl	$0, %ecx
	je		_start__search_right
	dec		%ecx
	movzbl	string_data(, %ecx, 1), %edi	# sizeof(char) == 1
	cmpl	%esi, %edi						# compare(key, data)
	jne		_start__search_right
	inc		%edx
	jmp		_start__search_left

_start__search_right:						# search right, until data != key
	movl	position, %ecx
	
_start__search_right_L0:
	inc		%ecx
	cmpl	string_data_act_len, %ecx
	je		_start__search_end
	movzbl	string_data(, %ecx, 1), %edi	# sizeof(char) == 1
	cmpl	%esi, %edi
	jne		_start__search_end
	inc		%edx
	jmp		_start__search_right_L0

_start__search_end:
	movl	%edx, counter
	M_write	$found_targets_prompt, $found_targets_prompt_len
	movl	counter, %edx
	pushl	%edx
	call	F_write_int
	call	F_writeln
	jmp		_start__exit

_start__not_found:
	M_write $not_found_prompt, $not_found_prompt_len	
	jmp		_start__exit

_start__exit:
	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$LINUX_SYS_CALL

