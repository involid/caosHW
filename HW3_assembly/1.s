	.text
	.global sum
    .global main
sum:
    //w0 = x0, x1 = N, x2 = *X
    mov x3, #0  //x3 = 0
    LoopBegin:
        cmp x3, x1  
        bge LoopEnd  // end loop if x3 >= x1

        ldr w4, [x2] // w4 = *X
        add w0, w0, w4 // x0 += x4
        add x2, x2, #4 // ++X

        add x3, x3, #1  // ++x3
        b LoopBegin
    LoopEnd:
    ret
