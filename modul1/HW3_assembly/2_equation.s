    .text
    .global solve

solve:
    //x0 = A, x1 = B, x2 = C, x3 = D
    mov x19, #0
    LoopBegin:
        cmp x19, #255
        bge LoopEnd // end loop if x19 > 254

        madd x20, x19, x0, x1 //x20 = x19 * x0 + x1
        madd x20, x19, x20, x2 //x20 = x19 * x20 + x2
        madd x20, x19, x20, x3 //x20 = x19 * x20 + x3

        cmp w20, #0
        beq LoopEnd // end loop if x20 == 0

        add x19, x19, #1 // ++x19
        b LoopBegin
    LoopEnd:
    mov x0, x19
    ret
