#### Предисловие ####

Если вы не уверены, стоит ли вам сначала пройти более ранние наши курсы, или у вас достаточно знаний, чтобы начать с «Красного пояса», попробуйте решить эту задачу. Если вы не понимаете её условие или не можете быстро решить, скорее всего, вам надо сначала пройти «Жёлтый пояс»

#### Условие задачи ####

Реализуйте шаблонную функцию

```objectivec
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate pred);
```

возвращающую итератор на максимальный элемент в диапазоне first, last, для которого предикат pred возвращает true. Если диапазон содержит несколько подходящих элементов с максимальным значением, то результатом будет первое вхождение такого элемента. Если диапазон не содержит подходящих элементов, то функция должна вернуть last.

#### Условие задачи ####

* pred принимает аргумент того типа, который имеют элементы диапазона
* для ForwardIterator определены операторы ++, ==, !=, * (разыменование)
* для типа, на который указывает итератор, определён оператор < («меньше»)

#### Заготовка решения: ####

[max_element_if.cpp](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_1/01%20Practice%20Programming%20Assignment/Source/max_element_if.cpp)

Автор задачи — Ольга Марчевская

P.S. В файле max_element_if.cpp используется заголовочный файл test_runner.h. Это юнит-тест фреймворк, который мы разработали в «Жёлтом поясе по C++».

[test_runner.h](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_1/01%20Practice%20Programming%20Assignment/Source/test_runner.h)