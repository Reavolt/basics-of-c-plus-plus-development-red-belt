##### Сортировка студентов по рейтингу #####

##### Условие #####

В данной задаче необходимо оптимизировать код, использующийся для сортировки студентов по рейтингу. Данные каждого студента находятся в структуре Student, объявленной в файле student.h. Рейтинг студента записан в поле rating:

```objectivec
struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};
```

Для сортировки студентов по рейтингу используется функция сравнения, возвращающая true, если рейтинг студента first выше рейтинга студента second.

```objectivec
bool Compare(Student first, Student second) {
  return first.Less(second);
}
```

Было выявлено, что эта функция является узким местом процесса сортировки, и именно её нужно оптимизировать.

Пришлите на проверку файл, содержащий оптимизированную версию функции Compare. Если ваша реализация будет недостаточно эффективной, то решение не уложится в ограничение по времени.\

[student.h](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_2/01%20Programming%20Assignment/Source/student.h)

[sort_students.cpp](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_2/01%20Programming%20Assignment/Source/sort_students.cpp)
