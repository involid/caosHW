    .intel_syntax noprefix

    .text
    .global dot_product

# extern float dot_product(size_t N, const float *A, const float *B);

# rdi = N, rsi = A, rdx = B
dot_product:
    xor r9, r9

    vxorps ymm2, ymm2, ymm2

    LoopBegin:
        add r9, 8
        cmp r9, rdi
        jg LoopEnd
        sub r9, 8

        vmovups ymm0, [rsi + 4*r9]
        vmovups ymm1, [rdx + 4*r9]
        vmulps ymm0, ymm0, ymm1

        vaddps ymm2, ymm2, ymm0

        add r9, 8
        jmp LoopBegin
    LoopEnd:
 
    vxorps ymm0, ymm0, ymm0
    vhaddps ymm2, ymm2, ymm0
    vhaddps ymm2, ymm2, ymm0
    vperm2f128 ymm1, ymm2, ymm0, 0b1
    vaddps ymm2, ymm2, ymm1
    vblendps ymm0, ymm0, ymm2, 0b1 

    sub r9, 8
    RemainderLoopBegin:
        cmp r9, rdi
        jz RemainderLoopEnd

        movss xmm1, [rsi + 4*r9]
        movss xmm2, [rdx + 4*r9]
        mulss xmm1, xmm2
        addss xmm0, xmm1

        inc r9
        jmp RemainderLoopBegin
    RemainderLoopEnd:

    ret
