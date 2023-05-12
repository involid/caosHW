    .intel_syntax noprefix

    .text
    .global mergesort

//void copy(int from, int to, int* in, int* out);
copy:
    push rdi
    mov r9, rdi

cpLoopBegin:
    cmp r9, rsi
    jz cpLoopEnd

    movsxd rdi, [rdx + 4*r9]
    mov [rcx + 4*r9], edi

    inc r9
    jmp cpLoopBegin
cpLoopEnd:
    pop rdi
    ret

//void merge(int from, int to, int* des, int* src, int mid);
merge:
    mov r9, rdi
    mov r10, r8
    mov r11, r9
mergeLoopBegin:
    //while (r9 < r8 && r10 < rsi)
    cmp r9, r8
    jz mergeLoopEnd
    cmp r10, rsi
    jz mergeLoopEnd

    push rbp
    push rbx
    movsxd rbp, [rcx + 4*r9]
    movsxd rbx, [rcx + 4*r10]
    cmp ebp, ebx
    jg caseGreater

caseLessOrEqual:
    mov [rdx + 4*r11], ebp
    inc r9
    inc r11
    pop rbx
    pop rbp
    jmp mergeLoopBegin

caseGreater:
    mov [rdx + 4*r11], ebx
    inc r10
    inc r11
    pop rbx
    pop rbp
    jmp mergeLoopBegin
mergeLoopEnd:

mergeLoop2Begin:
//while(r9 < r8)
    cmp r9, r8
    jz mergeLoop2End

    movsxd rax, [rcx + 4*r9]
    mov [rdx + 4*r11], eax
    inc r9
    inc r11

    jmp mergeLoop2Begin
mergeLoop2End:
    call copy
    ret


//extern void mergesort(int from, int to, const int *in, int *out);
mergesort:
    //allignment
    push rbp
    //rcx[] = rdx[]
    call copy

    mov rax, 4
    mul rdi
    add rcx, rax
    sub rsi, rdi

    push rsi
    push rcx
    mov rax, 4
    mul rsi
    mov rdi, rax
    call malloc
    mov rcx, rax
    pop rdx
    pop rsi
    xor rdi, rdi
    call copy

    call mergesortRecursion

    mov rsi, rcx
    call free
    pop rbp
    ret

mergesortRecursion:
    //check if to - from > 1
    dec rsi
    cmp rdi, rsi
    jz end
    inc rsi

    push r12
    push r13
    push r14

    //r14 = mid = (from + to) / 2
    //r12 = from
    mov r12, rdi
    //r13 = to
    mov r13, rsi

    //r14 = mid = (from + to) / 2
    mov r14, rdi
    add r14, rsi
    shr r14

    //mergesort(from, mid, in, out)
    mov rdi, r12
    mov rsi, r14
    call mergesortRecursion

    //mergesort(mid, to, in, out)
    mov rdi, r14
    mov rsi, r13
    call mergesortRecursion

    //merge(from, to, in, out, mid)
    mov rdi, r12
    mov rsi, r13
    mov r8, r14
    call merge

    pop r14
    pop r13
    pop r12
end:
    ret
