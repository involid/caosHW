    .intel_syntax noprefix

    .text
    .global very_important_function

very_important_function:
    push rbx
    push r12

    sub rsp, 8

    mov r12, rdi
    xor rbx, rbx

LoopBegin:
    cmp r12, rbx
    jz LoopEnd

    lea rdi, scanf_format_string[rip]
    mov rsi, rsp
    call scanf

    mov rsi, A[rip]
    movsxd rsi, [rsi + 4*rbx]
    movsxd rax, [rsp]
    mul rsi
    mov rsi, rax

    lea rdi, printf_format_string[rip]
    call printf

    inc rbx
    jmp LoopBegin
LoopEnd:

    add rsp, 8

    pop r12
    pop rbx

    ret

    .section .rodata
scanf_format_string:
    .string "%d"
printf_format_string:
    .string "%lld\n"
