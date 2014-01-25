	.section	__TEXT,__text,regular,pure_instructions
	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI0_0:
	.quad	4614955631756858884     ## double 3.452
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_dowork
	.align	4, 0x90
_dowork:                                ## @dowork
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$8000048, %rsp          ## imm = 0x7A1230
	movq	_attr@GOTPCREL(%rip), %rax
	leaq	-8000040(%rbp), %rsi
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	%rdi, -8000032(%rbp)
	movq	%rax, %rdi
	callq	_pthread_attr_getstacksize
	leaq	L_.str(%rip), %rdi
	movq	-8000032(%rbp), %rsi
	movq	-8000040(%rbp), %rdx
	movl	%eax, -8000044(%rbp)    ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$0, -8000020(%rbp)
	movl	%eax, -8000048(%rbp)    ## 4-byte Spill
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
	cmpl	$1000, -8000020(%rbp)   ## imm = 0x3E8
	jge	LBB0_8
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$0, -8000024(%rbp)
LBB0_3:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1000, -8000024(%rbp)   ## imm = 0x3E8
	jge	LBB0_6
## BB#4:                                ##   in Loop: Header=BB0_3 Depth=2
	leaq	-8000016(%rbp), %rax
	movl	$1000, %ecx             ## imm = 0x3E8
	movsd	LCPI0_0(%rip), %xmm0
	movl	-8000020(%rbp), %edx
	imull	-8000024(%rbp), %edx
	cvtsi2sdl	%edx, %xmm1
	divsd	%xmm0, %xmm1
	subl	-8000020(%rbp), %ecx
	cvtsi2sdl	%ecx, %xmm0
	addsd	%xmm0, %xmm1
	movslq	-8000024(%rbp), %rsi
	movslq	-8000020(%rbp), %rdi
	imulq	$8000, %rdi, %rdi       ## imm = 0x1F40
	addq	%rdi, %rax
	movsd	%xmm1, (%rax,%rsi,8)
## BB#5:                                ##   in Loop: Header=BB0_3 Depth=2
	movl	-8000024(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8000024(%rbp)
	jmp	LBB0_3
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_7
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-8000020(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8000020(%rbp)
	jmp	LBB0_1
LBB0_8:
	movabsq	$0, %rdi
	callq	_pthread_exit
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp7:
	.cfi_def_cfa_offset 16
Ltmp8:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp9:
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	movq	_attr@GOTPCREL(%rip), %rax
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	callq	_pthread_attr_init
	movq	_attr@GOTPCREL(%rip), %rdi
	leaq	-56(%rbp), %rsi
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	callq	_pthread_attr_getstacksize
	leaq	L_.str1(%rip), %rdi
	movq	-56(%rbp), %rsi
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str2(%rip), %rdi
	movq	$9000000, -56(%rbp)     ## imm = 0x895440
	movq	-56(%rbp), %rsi
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	_attr@GOTPCREL(%rip), %rdi
	movq	-56(%rbp), %rsi
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	callq	_pthread_attr_setstacksize
	leaq	L_.str3(%rip), %rdi
	movq	-56(%rbp), %rsi
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	$0, -72(%rbp)
	movl	%eax, -96(%rbp)         ## 4-byte Spill
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$4, -72(%rbp)
	jge	LBB1_6
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	movq	_attr@GOTPCREL(%rip), %rsi
	leaq	_dowork(%rip), %rdx
	leaq	-48(%rbp), %rax
	movq	-72(%rbp), %rcx
	shlq	$3, %rcx
	addq	%rcx, %rax
	movq	-72(%rbp), %rcx
	movq	%rax, %rdi
	callq	_pthread_create
	movl	%eax, -60(%rbp)
	cmpl	$0, -60(%rbp)
	je	LBB1_4
## BB#3:
	leaq	L_.str4(%rip), %rdi
	movl	-60(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	$4294967295, %edi       ## imm = 0xFFFFFFFF
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	callq	_exit
LBB1_4:                                 ##   in Loop: Header=BB1_1 Depth=1
	jmp	LBB1_5
LBB1_5:                                 ##   in Loop: Header=BB1_1 Depth=1
	movq	-72(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -72(%rbp)
	jmp	LBB1_1
LBB1_6:
	leaq	L_.str5(%rip), %rdi
	movq	-72(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movabsq	$0, %rdi
	movl	%eax, -104(%rbp)        ## 4-byte Spill
	callq	_pthread_exit
	.cfi_endproc

	.comm	_attr,64,3              ## @attr
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	 "Thread %ld: stack size = %li bytes \n"

L_.str1:                                ## @.str1
	.asciz	 "Default stack size = %li\n"

L_.str2:                                ## @.str2
	.asciz	 "Amount of stack needed per thread = %li\n"

L_.str3:                                ## @.str3
	.asciz	 "Creating threads with stack size = %li bytes\n"

L_.str4:                                ## @.str4
	.asciz	 "ERROR; return code from pthread_create() is %d\n"

L_.str5:                                ## @.str5
	.asciz	 "Created %ld threads.\n"


.subsections_via_symbols
