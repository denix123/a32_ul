
 
/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2010-2013 Mozilla Inc

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/



#include "pub_core_basics.h"
#include "pub_core_libcsetjmp.h"    





#if defined(VGP_ppc32_linux)

__asm__(
".text"  "\n"
""       "\n"
".global VG_MINIMAL_SETJMP"  "\n"  
"VG_MINIMAL_SETJMP:"  "\n"
"        stw     0, 0(3)"  "\n"
"        stw     1, 4(3)"  "\n"
"        stw     2, 8(3)"  "\n"
"        stw     3, 12(3)"  "\n"
"        stw     4, 16(3)"  "\n"
"        stw     5, 20(3)"  "\n"
"        stw     6, 24(3)"  "\n"
"        stw     7, 28(3)"  "\n"
"        stw     8, 32(3)"  "\n"
"        stw     9, 36(3)"  "\n"
"        stw     10, 40(3)"  "\n"
"        stw     11, 44(3)"  "\n"
"        stw     12, 48(3)"  "\n"
"        stw     13, 52(3)"  "\n"
"        stw     14, 56(3)"  "\n"
"        stw     15, 60(3)"  "\n"
"        stw     16, 64(3)"  "\n"
"        stw     17, 68(3)"  "\n"
"        stw     18, 72(3)"  "\n"
"        stw     19, 76(3)"  "\n"
"        stw     20, 80(3)"  "\n"
"        stw     21, 84(3)"  "\n"
"        stw     22, 88(3)"  "\n"
"        stw     23, 92(3)"  "\n"
"        stw     24, 96(3)"  "\n"
"        stw     25, 100(3)"  "\n"
"        stw     26, 104(3)"  "\n"
"        stw     27, 108(3)"  "\n"
"        stw     28, 112(3)"  "\n"
"        stw     29, 116(3)"  "\n"
"        stw     30, 120(3)"  "\n"
"        stw     31, 124(3)"  "\n"
         
"        mflr    4"  "\n"
"        stw     4, 128(3)"  "\n"
"        mfcr    4"  "\n"
"        stw     4, 132(3)"  "\n"
"        li      3, 0"  "\n"
"        blr"  "\n"
""       "\n"


".global VG_MINIMAL_LONGJMP"  "\n"
"VG_MINIMAL_LONGJMP:"  "\n"    
         
         
"        li      4, 1"  "\n"
"        stw     4, 12(3)"  "\n"
         
         
         
"        lwz     0, 128(3)"  "\n"
"        mtlr    0"  "\n"
"        lwz     0, 132(3)"  "\n"
"        mtcr    0"  "\n"
"        lwz     0, 0(3)"  "\n"
"        lwz     1, 4(3)"  "\n"
"        lwz     2, 8(3)"  "\n"
         
"        lwz     4, 16(3)"  "\n"
"        lwz     5, 20(3)"  "\n"
"        lwz     6, 24(3)"  "\n"
"        lwz     7, 28(3)"  "\n"
"        lwz     8, 32(3)"  "\n"
"        lwz     9, 36(3)"  "\n"
"        lwz     10, 40(3)"  "\n"
"        lwz     11, 44(3)"  "\n"
"        lwz     12, 48(3)"  "\n"
"        lwz     13, 52(3)"  "\n"
"        lwz     14, 56(3)"  "\n"
"        lwz     15, 60(3)"  "\n"
"        lwz     16, 64(3)"  "\n"
"        lwz     17, 68(3)"  "\n"
"        lwz     18, 72(3)"  "\n"
"        lwz     19, 76(3)"  "\n"
"        lwz     20, 80(3)"  "\n"
"        lwz     21, 84(3)"  "\n"
"        lwz     22, 88(3)"  "\n"
"        lwz     23, 92(3)"  "\n"
"        lwz     24, 96(3)"  "\n"
"        lwz     25, 100(3)"  "\n"
"        lwz     26, 104(3)"  "\n"
"        lwz     27, 108(3)"  "\n"
"        lwz     28, 112(3)"  "\n"
"        lwz     29, 116(3)"  "\n"
"        lwz     30, 120(3)"  "\n"
"        lwz     31, 124(3)"  "\n"
"        lwz     3, 12(3)"  "\n"
"        blr"  "\n"
""       "\n"

".previous"  "\n"
);

#endif 



#if defined(VGP_ppc64_linux)

__asm__(
".section \".toc\",\"aw\""          "\n"

".section \".text\""                "\n"
".align 2"                          "\n"
".p2align 4,,15"                    "\n"
".globl VG_MINIMAL_SETJMP"          "\n"

".section \".opd\",\"aw\""          "\n"
".align 3"                          "\n"
"VG_MINIMAL_SETJMP:"                "\n"
".quad .L.VG_MINIMAL_SETJMP,.TOC.@tocbase,0"   "\n"
".previous"                         "\n"

".type VG_MINIMAL_SETJMP, @function"   "\n"
".L.VG_MINIMAL_SETJMP:"   "\n"
"        std     0, 0(3)"  "\n"
"        std     1, 8(3)"  "\n"
"        std     2, 16(3)"  "\n"
"        std     3, 24(3)"  "\n"
"        std     4, 32(3)"  "\n"
"        std     5, 40(3)"  "\n"
"        std     6, 48(3)"  "\n"
"        std     7, 56(3)"  "\n"
"        std     8, 64(3)"  "\n"
"        std     9, 72(3)"  "\n"
"        std     10, 80(3)"  "\n"
"        std     11, 88(3)"  "\n"
"        std     12, 96(3)"  "\n"
"        std     13, 104(3)"  "\n"
"        std     14, 112(3)"  "\n"
"        std     15, 120(3)"  "\n"
"        std     16, 128(3)"  "\n"
"        std     17, 136(3)"  "\n"
"        std     18, 144(3)"  "\n"
"        std     19, 152(3)"  "\n"
"        std     20, 160(3)"  "\n"
"        std     21, 168(3)"  "\n"
"        std     22, 176(3)"  "\n"
"        std     23, 184(3)"  "\n"
"        std     24, 192(3)"  "\n"
"        std     25, 200(3)"  "\n"
"        std     26, 208(3)"  "\n"
"        std     27, 216(3)"  "\n"
"        std     28, 224(3)"  "\n"
"        std     29, 232(3)"  "\n"
"        std     30, 240(3)"  "\n"
"        std     31, 248(3)"  "\n"
         
"        mflr    4"  "\n"
"        std     4, 256(3)"  "\n"
"        mfcr    4"  "\n"
"        std     4, 264(3)"  "\n"
"        li      3, 0"  "\n"
"        blr"  "\n"
""       "\n"


".globl VG_MINIMAL_LONGJMP"         "\n"

".section \".opd\",\"aw\""          "\n"
".align 3"                          "\n"
"VG_MINIMAL_LONGJMP:"               "\n"
".quad .L.VG_MINIMAL_LONGJMP,.TOC.@tocbase,0"   "\n"
".previous" "\n"

".type   VG_MINIMAL_LONGJMP, @function"    "\n"
".L.VG_MINIMAL_LONGJMP:"            "\n"
         
         
"        li      4, 1"  "\n"
"        std     4, 24(3)"  "\n"
         
         
         
"        ld      0, 256(3)"  "\n"
"        mtlr    0"  "\n"
"        ld      0, 264(3)"  "\n"
"        mtcr    0"  "\n"
"        ld      0, 0(3)"  "\n"
"        ld      1, 8(3)"  "\n"
"        ld      2, 16(3)"  "\n"
         
"        ld      4, 32(3)"  "\n"
"        ld      5, 40(3)"  "\n"
"        ld      6, 48(3)"  "\n"
"        ld      7, 56(3)"  "\n"
"        ld      8, 64(3)"  "\n"
"        ld      9, 72(3)"  "\n"
"        ld      10, 80(3)"  "\n"
"        ld      11, 88(3)"  "\n"
"        ld      12, 96(3)"  "\n"
"        ld      13, 104(3)"  "\n"
"        ld      14, 112(3)"  "\n"
"        ld      15, 120(3)"  "\n"
"        ld      16, 128(3)"  "\n"
"        ld      17, 136(3)"  "\n"
"        ld      18, 144(3)"  "\n"
"        ld      19, 152(3)"  "\n"
"        ld      20, 160(3)"  "\n"
"        ld      21, 168(3)"  "\n"
"        ld      22, 176(3)"  "\n"
"        ld      23, 184(3)"  "\n"
"        ld      24, 192(3)"  "\n"
"        ld      25, 200(3)"  "\n"
"        ld      26, 208(3)"  "\n"
"        ld      27, 216(3)"  "\n"
"        ld      28, 224(3)"  "\n"
"        ld      29, 232(3)"  "\n"
"        ld      30, 240(3)"  "\n"
"        ld      31, 248(3)"  "\n"
"        ld      3, 24(3)"  "\n"
"        blr"               "\n"
""       "\n"

".previous"  "\n"
".previous"  "\n"
);

#endif 



#if defined(VGP_amd64_linux) || defined(VGP_amd64_darwin)

__asm__(
".text"  "\n"
""       "\n"

#if defined(VGP_amd64_linux)
".global VG_MINIMAL_SETJMP"  "\n"  
"VG_MINIMAL_SETJMP:"  "\n"

#elif defined(VGP_amd64_darwin)
".globl _VG_MINIMAL_SETJMP"  "\n"  
"_VG_MINIMAL_SETJMP:"  "\n"

#else
#   error "Huh?"
#endif

"        movq   %rax,   0(%rdi)"   "\n"
"        movq   %rbx,   8(%rdi)"   "\n"
"        movq   %rcx,  16(%rdi)"   "\n"
"        movq   %rdx,  24(%rdi)"   "\n"
"        movq   %rdi,  32(%rdi)"   "\n"
"        movq   %rsi,  40(%rdi)"   "\n"
"        movq   %rbp,  48(%rdi)"   "\n"
"        movq   %rsp,  56(%rdi)"   "\n"
"        movq   %r8,   64(%rdi)"   "\n"
"        movq   %r9,   72(%rdi)"   "\n"
"        movq   %r10,  80(%rdi)"   "\n"
"        movq   %r11,  88(%rdi)"   "\n"
"        movq   %r12,  96(%rdi)"   "\n"
"        movq   %r13, 104(%rdi)"   "\n"
"        movq   %r14, 112(%rdi)"   "\n"
"        movq   %r15, 120(%rdi)"   "\n"
         
"        movq   0(%rsp), %rax"     "\n"
"        movq   %rax, 128(%rdi)"   "\n"
         
"        movq   $0, %rax"          "\n"
"        ret"                      "\n"
""       "\n"


#if defined(VGP_amd64_linux)
".global VG_MINIMAL_LONGJMP"  "\n"
"VG_MINIMAL_LONGJMP:"  "\n"    

#elif defined(VGP_amd64_darwin)
".globl _VG_MINIMAL_LONGJMP"  "\n"
"_VG_MINIMAL_LONGJMP:"  "\n"    

#else
#   error "Huh?"
#endif
         
"        movq     8(%rdi),  %rbx"    "\n"
"        movq    16(%rdi),  %rcx"    "\n"
"        movq    24(%rdi),  %rdx"    "\n"
         
"        movq    40(%rdi),  %rsi"    "\n"
"        movq    48(%rdi),  %rbp"    "\n"
"        movq    56(%rdi),  %rsp"    "\n"
"        movq    64(%rdi),  %r8"     "\n"
"        movq    72(%rdi),  %r9"     "\n"
"        movq    80(%rdi),  %r10"    "\n"
"        movq    88(%rdi),  %r11"    "\n"
"        movq    96(%rdi),  %r12"    "\n"
"        movq   104(%rdi),  %r13"    "\n"
"        movq   112(%rdi),  %r14"    "\n"
"        movq   120(%rdi),  %r15"    "\n"
         
"        movq   128(%rdi), %rax"     "\n"
         
"        movq   32(%rdi), %rdi"      "\n"
         
"        addq   $8, %rsp"            "\n"
         
         
         
         
         
         
         
"        jmp *%rax"                  "\n"
""       "\n"

#if !defined(VGP_amd64_darwin)
".previous"       "\n"
#endif
);

#endif 



#if defined(VGP_x86_linux) || defined(VGP_x86_darwin)

__asm__(
".text"  "\n"
""       "\n"

#if defined(VGP_x86_linux)
".global VG_MINIMAL_SETJMP"  "\n"  
"VG_MINIMAL_SETJMP:"  "\n"

#elif defined(VGP_x86_darwin)
".globl _VG_MINIMAL_SETJMP"  "\n"  
"_VG_MINIMAL_SETJMP:"  "\n"

#else
#   error "Huh?"
#endif

"        movl   %eax,   0(%eax)"   "\n"
"        movl   %ebx,   4(%eax)"   "\n"
"        movl   %ecx,   8(%eax)"   "\n"
"        movl   %edx,  12(%eax)"   "\n"
"        movl   %edi,  16(%eax)"   "\n"
"        movl   %esi,  20(%eax)"   "\n"
"        movl   %ebp,  24(%eax)"   "\n"
"        movl   %esp,  28(%eax)"   "\n"
         
"        movl   0(%esp), %ebx"     "\n"
"        movl   %ebx, 32(%eax)"    "\n"
         
"        movl   4(%eax), %ebx"     "\n"
         
"        movl   $0, %eax"          "\n"
"        ret"                      "\n"
""       "\n"


#if defined(VGP_x86_linux)
".global VG_MINIMAL_LONGJMP"  "\n"
"VG_MINIMAL_LONGJMP:"  "\n"    

#elif defined(VGP_x86_darwin)
".globl _VG_MINIMAL_LONGJMP"  "\n"
"_VG_MINIMAL_LONGJMP:"  "\n"    

#else
#   error "Huh?"
#endif

         
"        movl     4(%eax),  %ebx"    "\n"
"        movl     8(%eax),  %ecx"    "\n"
"        movl    12(%eax),  %edx"    "\n"
"        movl    16(%eax),  %edi"    "\n"
"        movl    20(%eax),  %esi"    "\n"
"        movl    24(%eax),  %ebp"    "\n"
"        movl    28(%eax),  %esp"    "\n"
         
"        movl    32(%eax), %eax"     "\n"
         
"        addl    $4, %esp"           "\n"
         
         
"        jmp *%eax"                  "\n"
""       "\n"

#if !defined(VGP_x86_darwin)
".previous"       "\n"
#endif
);

#endif 

#if defined(VGP_mips32_linux)

__asm__(
".text                          \n\t"
".globl VG_MINIMAL_SETJMP;      \n\t"
".align 2;                      \n\t"
"VG_MINIMAL_SETJMP:             \n\t"  
"   sw   $s0,  0($a0)           \n\t"  
"   sw   $s1,  4($a0)           \n\t"
"   sw   $s2,  8($a0)           \n\t"
"   sw   $s3, 12($a0)           \n\t"
"   sw   $s4, 16($a0)           \n\t"
"   sw   $s5, 20($a0)           \n\t"
"   sw   $s6, 24($a0)           \n\t"
"   sw   $s7, 28($a0)           \n\t"
"   sw   $s8, 32($a0)           \n\t"  
"   sw   $ra, 36($a0)           \n\t"  
"   sw   $gp, 40($a0)           \n\t"  
"   sw   $sp, 44($a0)           \n\t"  

"   move $v0, $zero             \n\t"  
"   j    $ra                    \n\t"
"   nop                         \n\t"
".previous                      \n\t"
"                               \n\t"
".globl VG_MINIMAL_LONGJMP;     \n\t"
".align 2;                      \n\t"
"VG_MINIMAL_LONGJMP:            \n\t"  
"   lw   $s0,  0($a0)           \n\t"  
"   lw   $s1,  4($a0)           \n\t"
"   lw   $s2,  8($a0)           \n\t"
"   lw   $s3, 12($a0)           \n\t"
"   lw   $s4, 16($a0)           \n\t"
"   lw   $s5, 20($a0)           \n\t"
"   lw   $s6, 24($a0)           \n\t"
"   lw   $s7, 28($a0)           \n\t"
"   lw   $s8, 32($a0)           \n\t"  
"   lw   $ra, 36($a0)           \n\t"  
"   lw   $gp, 40($a0)           \n\t"  
"   lw   $sp, 44($a0)           \n\t"  

"   bnez $a1, 1f                \n\t"
"   nop                         \n\t"
"   addi $a1, $a1, 1            \n\t"  
"1:                             \n\t"
"   move $v0, $a1               \n\t"  
"   j    $ra                    \n\t"
"   nop                         \n\t"
".previous                      \n\t"
);
#endif  
