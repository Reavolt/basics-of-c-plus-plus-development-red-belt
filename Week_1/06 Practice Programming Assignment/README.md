##### Макрос UNIQ_ID #####

Разработать макрос UNIQ_ID, который будет формировать идентификатор, уникальный в пределах данного cpp-файла. Например, следующий код должен компилироваться и работать:

```objectivec
int UNIQ_ID = 5;
string UNIQ_ID = "hello!";
```

В рамках данной задачи допускается, что код

```objectivec
int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке
```

[uniq_id.cpp](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_1/06%20Practice%20Programming%20Assignment/Source/uniq_id.cpp)

не будет компилироваться. Заготовка решения:

##### Подсказки: #####

* подумайте, как можно применить макрос __LINE__
* ознакомьтесь с [конкатенацией в макросах](https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation)
* а также с [макросами в качестве параметров других макросов](https://stackoverflow.com/questions/4364971/and-in-macros)