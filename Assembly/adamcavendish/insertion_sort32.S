.file		"insertion_sort32.S"

.include	"linux_sys32.S"

.section .text

/**
 * @brief sort an array
 * @input	void
 *			insertion_sort(
 *				const void * ptr,
 *				size_t count,
 *				size_t size,
 *				int (*comp)(const void *, const void *))
 */
.type F_insertion_sort32, @function
.global F_insertion_sort32
F_insertion_sort32:
	/*
	@PARAMS
	movl	8(%ebp), %ebx			# array ptr
	movl	12(%ebp), %ecx			# array size
	movl	16(%ebp), %edi			# sizeof(array[0])
	movl	20(%ebp), %edx			# compare function
	*/

	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp				# allocate bytes for locals variables

	movl	$0, -4(%ebp)			# @LOCAL_VAR i at (%ebp - 4) = 0
	movl	$0, -8(%ebp)			# @LOCAL_VAR j at (%ebp - 8) = 0

	movl	16(%ebp), %edi			# @GET_PARAM sizeof(array[0])

	# malloc sizeof(array[0])
	/*
	movl	$sys_brk, %eax			# use 0 to get current program break
	xorl	%ebx, %ebx
	int		$LINUX_SYS_CALL			# %eax has the current program break
	movl	%eax, -12(%ebp)			# @LOCAL_VAR program_break at (%ebp-12)
	
	movl	%eax, %ebx				# %ebx = program_break
	addl	%edi, %ebx				# %ebx = program_break+sizeof(array[0])
	int		$LINUX_SYS_CALL			# allocate sizeof(array[0]) bytes
									#	--> temp
									# temp at (%eax - %edi)
									# temp's length = sizeof(array[0])
	subl	%edi, %eax
	movl	%eax, -16(%ebp)			# @LOCAL_VAR temp at (%ebp - 16)
	leal	-16(%ebp), %eax
	movl	%eax, -16(%ebp)
	*/
	/*
	pushl	%edi
	call	malloc
	movl	%eax, -16(%ebp)
	*/
	pushl	%ebp					# SAVE %ebp BEFORE CALL MMAP2
	movl	$sys_mmap2, %eax		# mmap sys_call
	xorl	%ebx, %ebx				# addr = NULL
	movl	16(%ebp), %ecx			# length = sizeof(array[0])
	movl	$3, %edx				# prot = PROT_READ|PROT_WRITE
	movl	$34, %esi				# flags = MAP_PRIVATE|MAP_ANONYMOUS
	movl	$-1, %edi				# fd = -1
	xorl	%ebp, %ebp				# offset = 0 (4096*0)
	int		$LINUX_SYS_CALL			# allocate sizeof(array[0]) bytes
									#	--> temp
	popl	%ebp					# RESTORE %ebp
	movl	%eax, -16(%ebp)			# @LOCAL_VAR temp at (%ebp - 16)

.local	outerloop
outerloop:
	movl	-4(%ebp), %ebx			# @LOCAL_VAR i
	cmpl	12(%ebp), %ebx			# i < array size ?
	jae		outerloop_end			

	movl	16(%ebp), %ecx			# @GET_PARAM sizeof(array[0])
	movl	8(%ebp), %edx			# @GET_PARAM array ptr
	imull	%ecx, %ebx				# i * sizeof(array[0])
	leal	(%edx, %ebx, 1), %esi	# %esi = array_ptr + i*sizeof(array[0])
	movl	-16(%ebp), %edi			# @LOCAL_VAR temp
	cld								# Clean the DIRECTION FLAG
	rep movsb						# memcpy(temp,
									#		array+i*sizeof(array[0]),
									#		sizeof(array[0]))

	movl	-4(%ebp), %ebx
	movl	%ebx, -8(%ebp)			# @LOCAL_VAR j = i
.local	innerloop
innerloop:
	movl	-8(%ebp), %ebx			# @LOCAL_VAR j
	cmpl	$0, %ebx				# j > 0?
	je		innerloop_end

	movl	-16(%ebp), %ebx			# @LOCAL_VAR temp
	pushl	%ebx					# compare function @PUT_PARAM 2nd = temp
	movl	-8(%ebp), %ebx			# @LOCAL_VAR j
	dec		%ebx					# j-1
	imull	16(%ebp), %ebx			# (j-1)*sizeof(array[0])
	addl	8(%ebp), %ebx			# array_ptr + (j-1)*sizeof(array[0])
	pushl	%ebx					# compare function @PUT_PARAM 1nd
									#	= array_ptr + (j-1)*sizeof(array[0])
	movl	20(%ebp), %ebx			# @GET_PARAM compare function
	call	*%ebx					# call the compare function
	cmpl	$0, %eax				# ret by compare > 0? (signed)
	jle		innerloop_end
	
	movl	16(%ebp), %ecx			# @GET_PARAM sizeof(array[0])
	movl	-8(%ebp), %ebx			# @LOCAL_VAR j
	movl	8(%ebp), %edx			# @GET_PARAM array ptr
	imull	%ecx, %ebx				# j * sizeof(array[0])
	leal	(%edx, %ebx, 1), %edi
									# %edi = array_ptr+j*sizeof(array[0])

	subl	%ecx, %ebx				# (j-1)*sizeof(array[0])
	leal	(%edx, %ebx, 1), %esi
									# %esi=array_ptr+(j-1)*sizeof(array[0])
	cld								# Clean the DIRECTION FLAG
	rep movsb						# memcpy(array+j*sizeof(array[0]),
									#		array+(j-1)*sizeof(array[0]),
									#		sizeof(array[0]))

	movl	-8(%ebp), %ebx			# @LOCAL_VAR --j
	dec		%ebx
	movl	%ebx, -8(%ebp)
	jmp		innerloop
.local	innerloop_end
innerloop_end:
	movl	16(%ebp), %ecx			# @GET_PARAM sizeof(array[0])
	movl	-8(%ebp), %ebx			# @LOCAL_VAR j
	movl	8(%ebp), %edi			# @GET_PARAM array ptr
	imull	%ecx, %ebx				# j * sizeof(array[0])
	leal	(%edi, %ebx, 1), %edi
									# %edi = array_ptr + j*sizeof(array[0])
	movl	-16(%ebp), %esi			# @LOCAL_VAR temp
	cld								# Clean the DIRECTION FLAG
	rep movsb						# memcpy(base + j*size, temp, size)

	movl	-4(%ebp), %ebx			# @LOCAL_VAR ++i
	inc		%ebx
	movl	%ebx, -4(%ebp)
	jmp		outerloop
.local	outerloop_end
outerloop_end:
	# free sizeof(array[0])
	/*
	movl	$sys_brk, %eax
	movl	-12(%ebp), %ebx			# @LOCAL_VAR preseved program_break
	int		$LINUX_SYS_CALL
	*/
	/*
	movl	-16(%ebp), %eax
	pushl	%eax
	call	free
	*/
	movl	$sys_munmap, %eax
	movl	-16(%ebp), %ebx			# @LOCAL_VAR pointer to temp
	movl	16(%ebp), %ecx			# temp's length = sizeof(array[0])
	int		$LINUX_SYS_CALL

	leave
	ret		$16

