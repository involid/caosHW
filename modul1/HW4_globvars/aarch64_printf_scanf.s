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
	// Сохраняем адрес возврата из main
	push x30

	// Первый аргумент - форматная строка
	adr x0, scanf_format

	// Выделяем на стеке место под значение, получаемое из scanf
	sub sp, sp, 16
	mov x1, sp // Второй аргумент - адрес для записи

	// Вызываем библиотечный scanf("%d", &a)
	bl scanf

	// На верхушке стека лежит число, полученное в scanf
	ldr x1, [sp]
	add sp, sp, 16

	// Первый аргумент - форматная строка
	adr x0, hello

	// Второй аргумент - число, получили чуть выше

	// Вызываем библиотечный printf("Hello World! %d\n", x1)
	bl printf

	// Возвращаем адрес возврата из main на место
	pop x30

	// Успех, нулевой код возврата
	mov x0, 0
	ret

	.section .rodata
hello:
	.string "Hello, World! %d\n"

scanf_format:
	.string "%d"
