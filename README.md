# C++ Labs 4th semester Anis Bouslama
### Задача 1
Дана текст и длина требуемой строки. Выровнять строки по центру. Обработать ситуации, когда строки исходного текста имеют длину больше, чем заданная длина (перенести лишние слова) и исходные строки не содержат пробелов.
Текст читаем из файла. Имя файла и длинна строки задаются с помощью аргументов командной строки. 
Приблизительный алгоритм:
1.	Читаем из файла построчно с помощью std::getline и ifstream
2.	Разбиваем строку на слова с помощью istream_iterator<string>
3.	Печатаем, полученные строчки, добавляя пробелы, если это необходимо
Обязательно использование STL структур данных, таких как std::vector и std::string и т.п. Везде, где это возможно, используем range for (for (auto &w : words) {).  
Для продвинутых, не использовать просто std::vector<std::string>, а оборачивать их в классы с конструкторами и соответствующими методами
### Задача 2
1.	Написать программу движения точки с расширяющимся и гаснущим следом. Управление движением точки осуществляется с помощью клавиш вправо, влево и вверх, вниз.
2.	Написать программу движения отрезка с расширяющимся и гаснущим следом. Управление движением отрезка осуществляется с помощью клавиш вправо, влево и вверх, вниз.

Все основные примитивы – позиция, скорость, отрезок должны использовать общий класс геометрический вектор. Операции с векторами реализовать с помощью операторов. 
### Задача 3
Написать систему меню. Система должна поддерживать:
-	Основное меню
-	Подменю 
-	Диалоговые окна 
Система должна описываться во внешнем файле ресурсов
В рамках этой задачи, необходимо:
-	Придумать формат файла и реализовать чтение элементов меню. Для этого использовать потоки и оператор чтения из потока, а также все что использовалось в первой задаче
-	Разработать механизм задания действий при нажатии на клавишу или выборе пункта меню
Графику делаем на GLUT.
