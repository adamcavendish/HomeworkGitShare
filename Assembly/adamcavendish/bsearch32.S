.file "bsearch32.S"

.include "linux_sys32.S"

.section .text
/**
 * @brief	binary search an array for a target
 * @input	void *
 *			bsearch(
 *				const void * key,
 *				const void * array,
 *				const size_t array_len,
 *				const size_t size = sizeof(array[0])
 *				int (*comp)(const void *, const void *));
 */
.type F_bsearch32, @function
.global F_bsearch32
F_bsearch32:
	/*
	@PARAMS
	movl	8(%ebp), %eax		# key
	movl	12(%ebp), %eax		# array
	movl	16(%ebp), %eax		# array_len
	movl	20(%ebp), %eax		# sizeof(array[0])
	movl	24(%ebp), %eax		# compare_function
	*/
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp

	movl	16(%ebp), %ecx		# @GET_PARAM array_len as @LOCAL_VAR i
	cmpl	$0, %ecx			# length <= 0, not found
	jle		RET_NFOUND
.local	L0_start
L0_start:
	shrl	$1, %ecx			# %ecx = i/2
	imull	20(%ebp), %ecx		# %ecx = (i/2)*sizeof(array[0])
	addl	12(%ebp), %ecx		# @GET_PARAM array
								# %ecx = array+(i/2)*sizeof(array[0]) --> pointer
	pushl	%ecx				# save %ecx

	movl	24(%ebp), %edi		# @GET_PARAM compare_function
	pushl	%ecx				# @PUT_PARAM 2nd = array+(i/2)*sizeof(array[0])
	pushl	8(%ebp)				# @PUT_PARAM 1st = key
	call	*%edi				# compare(key, array+(i/2)*sizeof(array[0])

	popl	%ecx				# @LOCAL_VAR pointer
	cmpl	$0, %eax			# check return == 0?
	je		RET_FOUND
	jl		L0_end

	addl	20(%ebp), %ecx		# pointer += sizeof(array[0])
	movl	%ecx, 12(%ebp)

	movl	16(%ebp), %ecx
	dec		%ecx				# @LOCAL_VAR --i
	movl	%ecx, 16(%ebp)
.local	L0_end
L0_end:
	movl	16(%ebp), %ecx		# @LOCAL_VAR i
	shrl	$1, %ecx			# @LOCAL_VAR i /= 2
	movl	%ecx, 16(%ebp)
	cmpl	$0, %ecx
	jnz		L0_start

.local	RET_NFOUND
RET_NFOUND:
	movl	$0, %eax
	leave
	ret		$20

.local	RET_FOUND
RET_FOUND:
	movl	%ecx, %eax
	leave
	ret		$20

