	.text
	.global main

	// Макросы для push и pop (можно и без них)
	.macro push Xn
		sub sp, sp, 16 // Выделяем место на стеке
		str \Xn, [sp]
	.endm

	.macro pop Xn
		ldr \Xn, [sp]
		add sp, sp, 16 // Освобождаем место на стеке
	.endm

main:
    push x30
    
    mov x0, 0
    mov x1, 0
    bl realloc //realloc(nullptr, 0) -> x0 = void*
    mov x19, 0 //x19 is loop counter
    mov x20, x0 //x20 is char*

input_loop_begin:
    bl getchar_unlocked //x0 is inputed char
    cmp w0, -1
    beq input_loop_end //end loop if x0 is EOF
    add x19, x19, 1 //++cn

    mov w21, w0 //inputed char -> w21

    mov x0, x20
    mov x1, x19
    bl realloc //x0 = realloc(x20, cn)
    mov x20, x0
    
    sub x19, x19, 1
    strb w21, [x20, x19] //x20[cn - 1] = 8 bytes of w21
    add x19, x19, 1

    b input_loop_begin
input_loop_end:

output_loop_begin:
    cmp x19, 0
    beq output_loop_end
    
    sub x19, x19, 1
    ldrb w0, [x20, x19] //x0 = 8 bytes of x20[cn - 1]
    bl putchar_unlocked //putchar_unlocked(x0)

    b output_loop_begin
output_loop_end:
    mov x0, x20
    bl free //free(x20)

    pop x30
    mov w0, 0
    ret
