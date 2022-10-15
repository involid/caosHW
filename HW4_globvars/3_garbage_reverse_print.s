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
    mov x19, 0
input_loop_begin:
    bl getchar_unlocked //x0 is inputed char
    cmp w0, -1
    beq input_loop_end //end loop if x0 is EOF

    push x0
    add x19, x19, 1

    b input_loop_begin
input_loop_end:

output_loop_begin:
    cmp x19, 0
    beq output_loop_end
    pop x0
    sub x19, x19, 1
    bl putchar_unlocked
    b output_loop_begin
output_loop_end:

    pop x30
    mov w0, 0
    ret
