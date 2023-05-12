#include <sys/syscall.h>
    .intel_syntax noprefix

    .text
    .global _start


_start:
    mov rax, SYS_brk
    mov rdi, 0
    syscall

    mov r12, rax // r12 will be pointer to back of text
    mov r13, rax // r13 will be pointer to top of text

    ReadingBegin:
        // allocating memory for buffer
        mov rdi, r13
        add rdi, 4096
        mov rax, SYS_brk
        syscall

        // calling syscall(SYS_read, 0, buff, 4096)
        mov rax, SYS_read
        mov rdi, 0
        mov rsi, r13
        mov rdx, 4096
        syscall

        // finish reading if read returned 0
        cmp rax, 0
        jz ReadingEnd

        // updating pointer to text top
        add r13, rax
        jmp ReadingBegin
    ReadingEnd:

    cmp r12, r13
    jz exit

    // placyng \n at the end if necessary
    dec r13
    mov al, [r13]
    mov bl, '\n'
    cmp al, bl
    jz added_endl

    mov rax, SYS_brk
    mov rdi, r13
    inc rdi
    syscall

    inc r13
    mov al, '\n'
    mov [r13], al

    added_endl:

    mov r14, 0 // r14 will be length of line
    writingBegin:
        cmp r13, r12
        jz writingEnd
        dec r13
        inc r14
        mov al, [r13]
        cmp al, '\n'
        jnz writingBegin

        // write line
        mov rax, SYS_write
        mov rdx, r14
        mov rdi, 1
        mov rsi, r13
        inc rsi
        syscall
        mov r14, 0
        jmp writingBegin
    writingEnd:

    mov rax, SYS_write
    inc r14
    mov rdx, r14
    mov rdi, 1
    mov rsi, r12
    syscall

    // free the memory
    mov rax, SYS_brk
    mov rdi, r12
    syscall

    exit:
    // calling SYS_exit
    mov rax, SYS_exit
    mov rdi, 0
    syscall