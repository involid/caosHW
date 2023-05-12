    .data
    .global R
R:  .space 8

    .text
    .global calculate

calculate:
    adr x0, .vars

    ldr x1, [x0]        // x1 <-- &A
    ldr x1, [x1]        // x1 <-- *A

    ldr x2, [x0, 8]     // B
    ldr x2, [x2]

    ldr x3, [x0, 16]    // C
    ldr x3, [x3]

    ldr x4, [x0, 24]    // D
    ldr x4, [x4]

    ldr x5, [x0, 32]    // x5 <-- &R

    mul x6, x1, x2      // x6 <-- A * B
    madd x7, x3, x4, x6 // x7 <-- C * D + (A * B)

    str x7, [x5]

    mov x0, x7

    ret

.vars:
    .quad   A
    .quad   B
    .quad   C
    .quad   D
    .quad   R
