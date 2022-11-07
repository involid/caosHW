    .intel_syntax noprefix

    .text
    .global very_important_function

    # rdi = N, rsi = A, rdx = B, rcx = R
//extern double very_important_function(size_t N, const float *A, const float *B, float *R);
very_important_function:
    mov r8, rdi # r8 = N, 
    mov r9, rdx # r9 = B, 

    vxorps ymm2, ymm2, ymm2 # after loop [R[7] + R[15] + ..., R[6] + R[14] + ..., ...]
    .Loop:
        sub rdi, 8
        mov rax, 4
        mul rdi

        vmovaps ymm0, [rsi + rax] 
        vmovaps ymm1, [r9 + rax]

        vaddps ymm0, ymm0, ymm1

        vmovaps [rcx + rax], ymm0

        vaddps ymm2, ymm2, ymm0

        cmp rdi, 0
        jg .Loop


    # after operations first 4 bytes of ymm2 is sum
    vxorps ymm0, ymm0, ymm0
    vhaddps ymm2, ymm2, ymm0
    vhaddps ymm2, ymm2, ymm0
    vperm2f128 ymm1, ymm2, ymm0, 0b1
    vaddps ymm2, ymm2, ymm1

    # ymm0 is sum
    vblendps ymm0, ymm0, ymm2, 0b1 

    # casts and finding answer
    vcvtss2sd xmm0, xmm0, xmm0 # xmm0 = (double) (float r8)
    vcvtsi2sd xmm1, xmm1, r8 # xmm1 = (double) (int64_t r8)
    divsd xmm0, xmm1 # xmm0 = xmm0 / xmm1

    ret
