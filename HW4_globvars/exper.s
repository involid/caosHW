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
    sub sp, sp, 16
    mov x0, 0

    mov x1, 0
    bl realloc

    mov x1, 100
    bl realloc

    add sp, sp, 16
    pop x30
    mov w0, 0
    ret
