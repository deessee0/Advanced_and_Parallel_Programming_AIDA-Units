	.file	"loop_unrolling.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sum = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%r12d, %r12d
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$8, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	.p2align 4,,10
	.p2align 3
.L2:
	call	rand@PLT
	addl	%eax, %r12d
	subl	$1, %ebx
	jne	.L2
	movl	$256, %ebx
	.p2align 4,,10
	.p2align 3
.L3:
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	call	rand@PLT
	addl	%eax, %r12d
	subl	$16, %ebx
	jne	.L3
	movl	%r12d, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
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
