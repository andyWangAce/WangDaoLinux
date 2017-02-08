	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"\345\217\252\346\234\211\344\270\200\344\270\252\345\217\202\346\225\260"
.LC1:
	.string	"rb+"
.LC2:
	.string	"fopen"
.LC3:
	.string	"success"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$1, -20(%rbp)
	jne	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L3
.L2:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L4
	movl	$.LC2, %edi
	call	perror
	movl	$-1, %eax
	jmp	.L3
.L4:
	movl	$.LC3, %edi
	call	puts
	movl	$1, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
