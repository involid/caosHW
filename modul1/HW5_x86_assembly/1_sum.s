    .intel_syntax noprefix

    .text
    .global sum

sum:
//rbc is counter
    push rbx 
    xor rbx, rbx

//r12 = N
    push r12 
    mov r12, rdi

//r13 = A
    push r13
    mov r13, rsi

//r14 = B
    push r14
    mov r14, rdx
    
//r15 = R
    push r15
    mov r15, rcx

    //5 * 8 = 30 bytes is pushed and rsp is alligned

LoopBegin:
    cmp r12, rbx
    jz LoopEnd

    movsxd rdi, [r13 + 4*rbx]
    movsxd rsi, [r14 + 4*rbx]
    add edi, esi
    mov [r15 + 4*rbx], edi

    inc rbx
    jmp LoopBegin
LoopEnd:

    pop rbx 
    pop r12 
    pop r13
    pop r14
    pop r15
    ret

    .section .rodata
scanf_format_string:
    .string "%d"
printf_format_string:
    .string "%lld\n"
