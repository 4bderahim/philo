	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_thread                 ## -- Begin function thread
	.p2align	4, 0x90
_thread:                                ## @thread
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rdi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	movq	%rdi, %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	xorl	%eax, %eax
	movl	%eax, %esi
	movl	$0, -4(%rbp)
	movl	$0, -20(%rbp)
	leaq	-16(%rbp), %rdi
	leaq	_thread(%rip), %rdx
	leaq	L_.str.1(%rip), %rcx
	callq	_pthread_create
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-16(%rbp), %rdi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	xorl	%r8d, %r8d
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%r8d, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"[+] Hello from thread!"

L_.str.1:                               ## @.str.1
	.asciz	"new thread"


.subsections_via_symbols
