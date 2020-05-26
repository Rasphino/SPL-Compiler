	.text
	.file	"main"
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$10, %edi
	callq	go
	movl	%eax, x(%rip)
	movl	$.L.str, %edi
	movl	%eax, %esi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.p2align	4, 0x90
	.type	pred__,@function
pred__:
	.cfi_startproc
	movl	%edi, %eax
	movb	%al, -1(%rsp)
	decb	%al
	movb	%al, -2(%rsp)
	retq
.Lfunc_end1:
	.size	pred__, .Lfunc_end1-pred__
	.cfi_endproc

	.p2align	4, 0x90
	.type	succ__,@function
succ__:
	.cfi_startproc
	movl	%edi, %eax
	movb	%al, -1(%rsp)
	incb	%al
	movb	%al, -2(%rsp)
	retq
.Lfunc_end2:
	.size	succ__, .Lfunc_end2-succ__
	.cfi_endproc

	.p2align	4, 0x90
	.type	fabs__,@function
fabs__:
	.cfi_startproc
	movsd	%xmm0, -8(%rsp)
	xorpd	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	ja	.LBB3_2
	subsd	-8(%rsp), %xmm1
	movsd	%xmm1, -16(%rsp)
.LBB3_2:
	movsd	-16(%rsp), %xmm0
	retq
.Lfunc_end3:
	.size	fabs__, .Lfunc_end3-fabs__
	.cfi_endproc

	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3
.LCPI4_0:
	.quad	4562254508917369340
.LCPI4_1:
	.quad	4611686018427387904
	.text
	.p2align	4, 0x90
	.type	sqrt__,@function
sqrt__:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 8(%rsp)
	movabsq	$4607182418800017408, %rax
	movq	%rax, (%rsp)
	.p2align	4, 0x90
.LBB4_1:
	movsd	(%rsp), %xmm0
	mulsd	%xmm0, %xmm0
	subsd	8(%rsp), %xmm0
	callq	fabs__
	ucomisd	.LCPI4_0(%rip), %xmm0
	jbe	.LBB4_3
	movsd	(%rsp), %xmm0
	movsd	8(%rsp), %xmm1
	divsd	%xmm0, %xmm1
	addsd	%xmm0, %xmm1
	divsd	.LCPI4_1(%rip), %xmm1
	movsd	%xmm1, (%rsp)
	jmp	.LBB4_1
.LBB4_3:
	movsd	(%rsp), %xmm0
	movsd	%xmm0, 16(%rsp)
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end4:
	.size	sqrt__, .Lfunc_end4-sqrt__
	.cfi_endproc

	.p2align	4, 0x90
	.type	odd__,@function
odd__:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	andl	$-2, %eax
	cmpl	%eax, %edi
	je	.LBB5_1
	movb	$1, -5(%rsp)
	movb	-5(%rsp), %al
	retq
.LBB5_1:
	movb	$0, -5(%rsp)
	movb	-5(%rsp), %al
	retq
.Lfunc_end5:
	.size	odd__, .Lfunc_end5-odd__
	.cfi_endproc

	.p2align	4, 0x90
	.type	abs__,@function
abs__:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	testl	%edi, %edi
	jle	.LBB6_2
	movl	-4(%rsp), %eax
	jmp	.LBB6_3
.LBB6_2:
	xorl	%eax, %eax
	subl	-4(%rsp), %eax
.LBB6_3:
	movl	%eax, -8(%rsp)
	movl	-8(%rsp), %eax
	retq
.Lfunc_end6:
	.size	abs__, .Lfunc_end6-abs__
	.cfi_endproc

	.p2align	4, 0x90
	.type	sqr__,@function
sqr__:
	.cfi_startproc
	movl	%edi, %eax
	movl	%edi, -4(%rsp)
	imull	%edi, %eax
	movl	%eax, -8(%rsp)
	retq
.Lfunc_end7:
	.size	sqr__, .Lfunc_end7-sqr__
	.cfi_endproc

	.p2align	4, 0x90
	.type	go,@function
go:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	%edi, 20(%rsp)
	leal	-1(%rdi), %eax
	movl	%eax, 16(%rsp)
	leal	-2(%rdi), %eax
	movl	%eax, 12(%rsp)
	cmpl	$1, %edi
	je	.LBB8_1
	cmpl	$2, 20(%rsp)
	jne	.LBB8_4
.LBB8_1:
	movl	$1, 8(%rsp)
	jmp	.LBB8_2
.LBB8_4:
	movl	16(%rsp), %edi
	callq	go
	movl	%eax, 8(%rsp)
	movl	12(%rsp), %edi
	callq	go
	addl	%eax, 8(%rsp)
.LBB8_2:
	movl	8(%rsp), %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end8:
	.size	go, .Lfunc_end8-go
	.cfi_endproc

	.type	x,@object
	.bss
	.globl	x
	.p2align	2
x:
	.long	0
	.size	x, 4

	.type	.L.str,@object
	.section	.rodata,"a",@progbits
.L.str:
	.asciz	"%d \n"
	.size	.L.str, 5

	.section	".note.GNU-stack","",@progbits
