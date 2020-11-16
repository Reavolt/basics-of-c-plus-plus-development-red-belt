## Move-семантика в SimpleVector ##

### Условие ###

Решите задачу [«Реализовать свой вектор»](https://www.coursera.org/learn/c-plus-plus-red/programming/dt1wy/pishiem-svoi-viektor) со следующими дополнительными требованиями:

* метод PushBack должен позволять добавить элемент в вектор с помощью перемещения;
* никакие методы вектора не должны осуществлять копирование элементов.

Таким образом, должен получиться вектор, позволяющий хранить некопируемые объекты.

Шаблон решения содержит юнит-тест, проверяющий работу вектора, состоящего из некопируемых строк. Если вектор будет осуществлять копирования, благодаря указанному юнит-тесту **решение не скомпилируется**.

### Файл с заготовкой решения ###

[simple_vector_2.h](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_5/05%20Practice%20Programming%20Assignment/Source/simple_vector_2.h)

[simple_vector_2.cpp](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_5/05%20Practice%20Programming%20Assignment/Source/simple_vector_2.cpp)