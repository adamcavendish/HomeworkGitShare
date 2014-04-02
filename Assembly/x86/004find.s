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
.ascii			"Please input A char for search:\n"
				search_prompt_len =			. - search_prompt

				reinput_prompt:
.ascii			"We need only one character. Please Reinput:\n"
				reinput_prompt_len =		. - reinput_prompt

				found_pos_prompt:
.ascii			"Found Positions Are:\n"
				found_pos_prompt_len =		. - found_pos_prompt
# RODATA END

# DATA SECTION
.section .data
				string_data_len =			50
.lcomm			string_data,				string_data_len
				string_data_act_len:		.int	0

				counter:					.int	0
				position:					.int	0

# DATA SECTION END

# BSS SECTION
.section .bss
				buffer_len =				50
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
	M_write $found_pos_prompt, $found_pos_prompt_len
	xorl	%eax, %eax
	movl	%eax, counter					# counter = 0

	pushl	string_data_act_len				# @PUT_PARAM 2nd, array_len
	pushl	$string_data					# @PUT_PARAM 1st, array
	call	search_aux
	cmpl	$0, %eax						# return NULL?
	je		search_aux__searching_end
	subl	$string_data, %eax
	
	movl	%eax, position
	pushl	%eax
	call	F_write_int
	call	F_writeln


	# exit
	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$LINUX_SYS_CALL

/**
 *	@input	void search_aux(
 *				const void * array
 *				const void * array_len)
 */
.type	search_aux, @function
search_aux:
	pushl	%ebp
	movl	%esp, %ebp

search_aux__searching_loop:
	pushl	$F_compare_char					# @PUT_PARAM 5th, compare_function
	pushl	$1								# @PUT_PARAM 4th, sizeof(array[0])
	pushl	12(%ebp)						# @PUT_PARAM 3rd, @GET_PARAM array_len
	pushl	8(%ebp)							# @PUT_PARAM 2nd, @GET_PARAM array
	leal	buffer, %eax
	pushl	%eax							# @PUT_PARAM 1st, key
	call	F_bsearch32
	cmpl	$0, %eax						# return NULL?
	je		search_aux__searching_end
	subl	$string_data, %eax
	
	movl	%eax, position
	pushl	%eax
	call	F_write_int
	call	F_writeln

	movl	counter, %eax
	inc		%eax
	movl	%eax, counter

	movl	position, %eax
	pushl	%eax							# @PUT_PARAM 2nd, position
	pushl	8(%ebp)							# @PUT_PARAM 1st, array
	call	search_aux						# recursive call

	movl	string_data_act_len, %eax
	subl	position, %eax
	pushl	%eax							# @PUT_PARAM 2nd, position
	movl	8(%ebp), %eax
	addl	position, %eax
	inc		%eax
	pushl	%eax							# @PUT_PARAM 1st, array+position+1
	call	search_aux						# recursive call

	jmp		search_aux__searching_loop

search_aux__searching_end:
	leave
	ret		$8

