Вам дан класс Logger и макрос LOG

```objectivec
class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) ...
```

Параметры макроса LOG — объект класса Logger и строковое сообщение, которое должно быть передано в метод Log. В зависимости от настроек объекта класса Logger логируемое сообщение должно предваряться именем файла или номером строки. Смотрите юнит-тесты в заготовке решения для более подробного описания поведения.

Реализуйте макрос LOG так, чтобы он добавлял в логируемое сообщение имя файла и номер строки в зависимости от настроек объекта logger. Пришлите на проверку cpp-файл, содержащий

* реализацию макроса LOG
* объявление класса Logger, при этом вы можете при необходимости добавлять в него дополнительные поля и методы
* определения всех методов класса Logger

[log.cpp](https://github.com/Hitoku/basics-of-c-plus-plus-development-red-belt/blob/master/Week_1/02%20Practice%20Programming%20Assignment/Source/log.cpp)

##### Замечание #####

Если вы используете Visual Studio, у вас могут не проходить юнит-тесты из заготовки, потому что в этой среде макрос __FILE__ раскрывается в абсолютный путь до файла. Учитывайте это при отладке своего решения.