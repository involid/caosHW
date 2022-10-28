	.text
	.global f
	.global main

f:
	// A = x0, B = x1, C = x2, x = x3

	// Посчитаем результат выражения в регистре x4
	// x4 = Ax + B
    madd x4, x0, x3, x1 // x0 * x3 + x1
	// x4 = Ax^2 + Bx + C
    madd x4, x4, x3, x2

	// Возвращаемое значение должно лежать в регистре x0
	mov x0, x4 // x0 = Ax^2 + Bx + C
	ret
