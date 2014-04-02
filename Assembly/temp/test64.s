.data
data:
	.int	1024
int_val:
	.int	0

.text
.global _start
_start:
	callq	ABC
	movq	ABC, %rax
	pushq	%rax
	popq	%rax

	movq	%rax, %rbx
	leaq	data, %rax
	movq	data, %rax

	movq	$15, (%rax)

	movq	$1, %rax
	movq	$0, %rbx
	int		$0x80

ABC:
	movq	$100, %rbx
	ret

