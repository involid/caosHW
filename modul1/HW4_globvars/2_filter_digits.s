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

loop_begin:
    bl getchar_unlocked //x0 is inputed char
    cmp w0, -1
    beq loop_end //end loop if x0 is EOF

    cmp w0, 47
    blt loop_begin //if w0 <= '0' continue

    cmp w0, 58
    bge loop_begin //if w0 > '9' continue

    bl putchar_unlocked
    b loop_begin
loop_end:

    pop x30
    mov w0, 0
    ret
