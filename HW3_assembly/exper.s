    .text
    .global solve

solve:
    //x0 = A, x1 = B, x2 = C, x3 = D
    mov x19, #1

    madd x20, x19, x0, x1 //x20 = x19 * x0 + x1
    madd x20, x19, x20, x2 //x20 = x19 * x20 + x2
    madd x20, x19, x20, x3 //x20 = x19 * x20 + x3

    cmp w20, wzr
    beq aa
    ret
aa:
    mov x0, #40
    ret
