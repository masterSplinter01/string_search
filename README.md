Поиск подстроки в файлах.

Запуск программы: 
string_search.exe -p C:\Temp -m *.* -i String.txt -o Result.txt

Вводимые данные: 
  1. директория, в которой производится поиск
  2. маска имен файлов, в которых осуществляется поиск
  3. файл с искомой подстрокой
  4. файл с результатами

Для поиска был выбран алгоритм Рабина-Карпа.

Структура:

  Класс substring - класс, хранящий сведения об искомой подстроке: путь к файлу, хэш, длина, p^длина_подстроки
  
  Функция search_substring, запускающая прохождение по папке
  
  Функция rabin_karp_search - поиск подстроки в строке
  
Для работы необходима библиотека Boost
  
