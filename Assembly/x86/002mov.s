.include "linux_sys32.S"

.data
# STRING VALUES
mystr:
	.ascii	"Hello World"	# Text String
	len = . - mystr
mystr2:
	.asciz	"Assembly Language"	# Null-terminated Text String

# INTEGER VALUES
bval:
	.byte	1			# 8-bit
sval:
	.short	2			# 16-bit
ival:
	.int	2			# 32-bit
lval:
	.long	3			# 32-bit(flag --32)

qval:
	.quad	5			# 8-bit
oval:
	.octa	4			# 16-bit
word:
	.word	6			# 32-bit

# LIST OF VALUES
arr:
	.int	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

# FLOATING VALUES
db_val:
	.double	3.1415926
ft_val:
	.float	2.71828
sn_val:
	.single	2.71828

# CONST VALUE
	.equ LINUX_SYS_CALL, 0x80	# use $LINUX_SYS_CALL to access

buffer3:
#	.fill	30000			# initialized buffer

# BUFFERS
.section .bss
	.comm	buffer1, 10000	# global uninitialized buffer
	.lcomm	buffer2, 20000	# local uninitialized buffer

.text
.global _start
_start:
	movl	$100, %eax		# immediate data to GReg
	movl	$0xF, %eax

	movl	$101, ival		# immediate data to memory location

	movl	%eax, %ebx		# GReg to GReg 32-bit
	movl	$0, %ebx
	movw	%ax, %bx		# GReg to GReg 16-bit
	movl	$0, %ebx
	movb	%al, %bl		# GReg to GReg 8-bit
	movl	$0, %ebx

	movl	%eax, ival		# GReg to memory location
	movl	$0, ival
	movl	ival, %eax		# memory location to GReg

	# indexed memory location
	# format: base(offset, index, size) = base + offset + index * size
	movl	$2, %edi
	movl	arr(, %edi, 4), %eax

	# using address
	movl	$arr, %edi		# move the address of 'arr' into %edi
	movl	%eax, 4*4(%edi)

	movl	%ds, %eax		# Segment Reg to GReg
	movl	%ebx, %ds		# GReg to Segment Reg
	movl	%eax, %ds

	movl	$sys_exit, %eax
	movl	$0, %ebx
	int		$LINUX_SYS_CALL

