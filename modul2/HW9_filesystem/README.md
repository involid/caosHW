## Problem 0

Программе на стандартном потоке ввода передаётся список имён файлов.

Необходимо посчитать суммарный размер в байтах всех файлов, которые являются регулярными.

## Problem 1
Программе на стандартном потоке ввода передаётся список имён файлов.

Необходимо вывести на стандартный поток вывода имена "неправильных" выполняемых файлов, то есть файлов, которые отмечены как исполняемые, но при этом они заведомо не могут быть выполнены в системе (не начинаются с корректной строки #!, содержащей запускаемый интерпретатор, и не являются ELF-файлами).

## Problem 2
Реализуйте функцию

```
extern void normalize_path(char * path);
```
которая обрабатывает строки, представляющие пути к файлам (заканчиваются на любой символ, отличный от /) или каталогам (заканчиваются на символ /).

Функция должна привести текст в каноническую форму:

1. убрать дублирование подряд идущих символов /
2. обработать фрагменты ./ и ../
Запрещается использовать библиотечные строковые функции.

Запрещается выделять память под новую строку, - используйте уже существующую, аргумент не является константной строкой.

Используйте арифметику указателей; запрещается обращение к символам как к элементам массива.

## Problem 3
Программе на стандартном потоке ввода передаётся список имён файлов.

Если файл является символической ссылкой, то нужно вывести абсолютное имя того файла, на который эта ссылка указывает.

Если файл является регулярным, то необходимо создать символическую ссылку в текущем каталоге, приписав в названии файла префикс link_to_.