#include <sys/syscall.h>
    .intel_syntax noprefix

    .text
    .global _start

_start:
    sub sp, 4096 // take a space for buffer
    
    LoopBegin:
        // callig read(0, buff, 4096)
        mov rax, SYS_read
        mov rdi, 0
        mov rsi, rsp
        mov rdx, 4096
        syscall

        // finish reading if read returned 0
        cmp rax, 0
        jz LoopEnd

        // calling write(1, buff, readed_size)
        mov rdx, rax
        mov rax, SYS_write
        mov rdi, 1
        mov rsi, rsp
        syscall

        jmp LoopBegin
    LoopEnd:
    
    add sp, 4096 // free buffer space
    
    //calling SYS_exit
    mov rax, SYS_exit
    mov rdi, 0
    syscall