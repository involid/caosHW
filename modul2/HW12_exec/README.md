## Problem 0
Программе на стандартный поток ввода задается некоторое арифметическое выражение в синтаксисе языка python3.

Необходимо вычислисть это выражение, и вывести результат.

Использовать дополнительные процессы запрещено.

## Problem 1
Программе на стандартном потоке ввода задается выражение в синтаксисе языка Си.

Необходимо вычислить значение этого выражения (итоговый результат представим типом int) и вывести его на стандартный поток вывода.

## Problem 2
Программе на стандартном потоке ввода задается текст вида


```
GET /some_path/script.py?a=123&b=abrakadabra HTTP/1.1
Host: www.example.com
```

Обратите внимание на последнюю пустую строку.

Необходимо сформировать и вывести на стандартный поток вывода HTTP-ответ, который в случае успеха имеет вид:

```
HTTP/1.1 200 OK
[содержимое вывода скрипта]
```
Если указанный файл не существует, то необходимо вывести текст

```
HTTP/1.1 404 ERROR
```

Если файл существует, но не является выполняемым, то текст

```
HTTP/1.1 403 ERROR
```

У скрипта могут (но не обязаны) быть CGI-параметры, которые ему нужно передавать для обработки.

Необходимо реализовать поддержку только GET-запросов, но не POST.

Гарантируется, что входные данных содержат только синтаксически корректные запросы.

Необходимо реализовать поддержку следующих переменных окружения:

* HTTP_HOST
* QUERY_STRING
* REQUEST_METHOD
* SCRIPT_NAME
