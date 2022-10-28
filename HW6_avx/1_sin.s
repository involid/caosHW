    .intel_syntax noprefix

    .text
    .global avx_sin

# extern double avx_sin(double x)
# sinx = sum( (-1)^n * x^(2n+1) / (2n+1)! ) = x - x^3 / 3! + x^5 / 5! - x^7 / 7! + ...
# xmm0 = x
# xmm1 = -x^2
# xmm2 = 2n + 1
# xmm3 = (-1)^n * x^(2n+1) / (2n+1)!

avx_sin:
    # xmm1 = -x^2 
    mov rdi, -1
    vcvtsi2sd xmm1, xmm1, rdi
    vmulpd xmm1, xmm1, xmm0
    vmulpd xmm1, xmm1, xmm0

    # xmm2 = xmm3 = 1
    mov rdi, 1
    vcvtsi2sd xmm2, xmm2, rdi
    vmovapd xmm3, xmm2

    movupd xmm4, xmm0  # xmm4 = x
    vxorpd xmm5, xmm5, xmm5 # xmm5 = 0
    .Loop:
        vmulpd xmm4, xmm4, xmm1 # xmm3 *= -x^2

        vaddpd xmm2, xmm2, xmm3 # ++xmm2
        divpd xmm4, xmm2
        vaddpd xmm2, xmm2, xmm3 # ++xmm2
        divpd xmm4, xmm2

        vaddpd xmm0, xmm0, xmm4

        vcomisd xmm4, xmm5
        jnz .Loop

    ret
