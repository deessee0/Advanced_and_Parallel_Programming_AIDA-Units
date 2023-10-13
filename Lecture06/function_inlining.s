	.file	"function_inlining.c"
	.text
	.p2align 4
	.globl	g
	.type	g, @function
g:
.LFB40:
	.cfi_startproc
	endbr64
	movl	%edi, %edx
	movl	%esi, %ecx
	cmpl	%esi, %edi
	jge	.L7
	movl	%esi, %edi
	subl	%edx, %edi
	leal	-1(%rdi), %eax
	cmpl	$9, %eax
	jbe	.L8
	movd	%edx, %xmm4
	movl	%edi, %esi
	movdqa	.LC1(%rip), %xmm3
	xorl	%eax, %eax
	pshufd	$0, %xmm4, %xmm1
	paddd	.LC0(%rip), %xmm1
	shrl	$2, %esi
	pxor	%xmm0, %xmm0
	.p2align 4,,10
	.p2align 3
.L4:
	movdqa	%xmm1, %xmm2
	addl	$1, %eax
	paddd	%xmm3, %xmm1
	paddd	%xmm2, %xmm0
	cmpl	%esi, %eax
	jne	.L4
	movdqa	%xmm0, %xmm1
	movl	%edi, %esi
	psrldq	$8, %xmm1
	andl	$-4, %esi
	paddd	%xmm1, %xmm0
	addl	%esi, %edx
	movdqa	%xmm0, %xmm1
	psrldq	$4, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	cmpl	%esi, %edi
	je	.L11
.L3:
	leal	1(%rdx), %esi
	addl	%edx, %eax
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	2(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	3(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	4(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	5(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	6(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	7(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	leal	8(%rdx), %esi
	cmpl	%esi, %ecx
	jle	.L1
	addl	%esi, %eax
	addl	$9, %edx
	leal	(%rax,%rdx), %esi
	cmpl	%edx, %ecx
	cmovg	%esi, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	xorl	%eax, %eax
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	ret
.L8:
	xorl	%eax, %eax
	jmp	.L3
	.cfi_endproc
.LFE40:
	.size	g, .-g
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"x = %d\ny = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$145, %ecx
	movl	$145, %edx
	xorl	%eax, %eax
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
