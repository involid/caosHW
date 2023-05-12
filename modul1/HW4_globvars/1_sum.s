	.text
	.global main

	// Макросы для push и pop
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

    adr x0, scanf_format
    sub sp, sp, 16
    mov x1, sp
    bl scanf //вводим первое число на верхушку стека
    
    adr x0, scanf_format
    sub sp, sp, 16
    mov x1, sp
    bl scanf //вводим второе число на верхушку стека

    pop x2
    pop x1 // берем 2 9исла из стека
    add w1, w1, w2 // сохроняем сумму в x0
    adr x0, scanf_format
    bl printf //printf("%d", x0)

    pop x30
    mov x0, 0
    ret

.section .rodata
scanf_format: .string "%d"
