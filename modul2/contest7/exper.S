#include <sys/syscall.h>

    .text
    .globl _start
_start:
    movq $SYS_brk, %rax
    movq $0x0, %rdi
    syscall

    movq %rax, %r8

    movq $SYS_brk, %rax
    movq $0x2000000, %rdi
    syscall

    movq %r8, %r9
    movq $0x2000000, %r10
read:
    movq $SYS_read, %rax
    movq $0x0, %rdi
    movq %r9, %rsi
    movq %r10, %rdx
    syscall

    or %rax, %rax
    jz end_read

    addq %rax, %r9
    subq %rax, %r10

    jmp read
end_read:

    cmp %r8, %r9
    je exit

    dec %r9

    movb (%r9), %r10b
    movb $0x0A, %r11b
    cmp %r10b, %r11b
    je write

    inc %r9
    movb $0x0A, (%r9)

write:
    movq %r9, %rbx
    dec %rbx
find:
    cmp %rbx, %r8
    je end_write

    movb (%rbx), %r11b
    movb $0x0A, %r12b
    cmp %r11b, %r12b
    je end_find

    dec %rbx
    jmp find
end_find:

    movq $SYS_write, %rax
    movq $0x1, %rdi
    movq %rbx, %rsi
    inc %rsi
    movq %r9, %rdx
    subq %rbx, %rdx
    syscall

    movq %rbx, %r9
    jmp write

end_write:
    movq $SYS_write, %rax
    movq $0x1, %rdi
    movq %rbx, %rsi
    movq %r9, %rdx
    subq %rbx, %rdx
    inc %rdx
    syscall    

exit:
    movq $SYS_exit, %rax
    xorq %rdi, %rdi
    syscall