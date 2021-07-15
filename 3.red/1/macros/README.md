# Макрос LOG

Вам дан класс Logger и макрос LOG

```c++
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

## Замечание
Если вы используете Visual Studio, у вас могут не проходить юнит-тесты из заготовки, потому что в этой среде макрос __FILE__ раскрывается в абсолютный путь до файла. Учитывайте это при отладке своего решения.

## Решение
    log.cpp

# Генератор компараторов

Давайте представим, что вы разрабатываете инновационный сервис поиска авиабилетов AviaScanner. В вашем сервисе авиабилет представляется в виде структуры 

```c++
struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  uint64_t price;
};
```
В данный момент вы работаете над функцией сортировки результатов поиска. Пользователь вводит свой запрос и получает список подходящих билетов. Дальше он может задавать параметры сортировки этого списка. Например, сначала по цене, затем по времени вылета и, наконец, по аэропорту прилёта.

Чтобы реализовать сортировку как в примере, можно воспользоваться алгоритмом цифровой сортировки:

```c++
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.to < rhs.to;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.departure_time < rhs.departure_time;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.price < rhs.price;
  });
}
```

Как видите, в примере выше есть дублирование кода — нам пришлось написать три лямбда-функции, которые отличаются только полем, по которому выполняется сортировка. От этого дублирования можно избавиться, написав макрос SORT_BY и применив его следующим образом:

```c++
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), SORT_BY(to));
  stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
```

Напишите макрос SORT_BY, который принимает в качестве параметра имя поля структуры AirlineTicket. Вызов sort(begin(tixs), end(tixs), SORT_BY(some_field)) должен приводить к сортировке вектора tixs по полю some_field.

Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket, а также заготовка решения в виде cpp-файла sort_by.cpp. Пришлите на проверку cpp-файл, который
* подключает заголовочный файл airline_ticket.h
* содержит макрос SORT_BY
* содержит определения операторов, необходимых для использования классов Date и Time в алгоритме сортировки и макросе ASSERT_EQUAL (формат вывода в поток можете выбрать произвольный)

## Решение
    airlines/sort.by

# Макрос UPDATE_FIELD

Продолжим работу над сервисом поиска авиабилетов AviaScanner. Наш сервис хранит базу данных билетов в виде vector<AirlineTicket>, где AirlineTicket — такая же структура, как и в предыдущей задаче. Периодически наш сервис обходит сайты авиакомпаний, собирает свежую информацию о доступных билетах и обновляет записи в своей базе данных. Делается это с помощью функции void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates). Параметр updates содержит пары (имя поля; новое значение). При этом он содержит только те поля, которые поменялись. Пример работы функции UpdateTicket:

```c++
void UpdateTicketExample() {
  AirlineTicket t;
  t.price = 5000;
  t.from = "DME";
  t.to = "AER";

  const map<string, string> updates = {
    {"price", "3500"},
    {"from", "VKO"}
  };
  UpdateTicket(t, updates);
  ASSERT_EQUAL(t.from, "VKO");
  ASSERT_EQUAL(t.to, "AER");
  ASSERT_EQUAL(t.price, 3500);
}
```

  Функцию UpdateTicket можно было бы реализовать так:

```c++
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

  ...
}
```

Здесь налицо дублирование кода — блоки кода внутри функции UpdateTicket отличаются только именем поля (конечно, первые два блока не такие, как третий, но их легко к нему свести). При этом имя поля используется не только для обращения к структуре AirlineTicket, но и как строковый литерал. Поэтому можно написать макрос, который существенно упростит функцию UpdateTicket:  

```c++
#define UPDATE_FIELD(ticket, field, values) ...

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
  ...
}
```

Напишите макрос UPDATE_FIELD. Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket, а также заготовка решения в виде cpp-файла update_field.cpp. Пришлите на проверку cpp-файл, который
* подключает заголовочный файл airline_ticket.h
* содержит макрос UPDATE_FIELD
* содержит определения операторов, необходимых для считывания классов Date и Time из потока istream и их использования в макросе ASSERT_EQUAL (формат ввода смотрите в юнит-тестах в файле update_field.cpp)

## Решение
    airlines/update_field.cpp

# Плохой макрос

Вам дан макрос, который распечатывает два переданных ему значения в переданный поток вывода. В реализации макроса есть недостаток, ограничивающий его применимость в реальных программах. Вам требуется найти и устранить недостаток.  

```c++
#define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
```

## Решение
    bad_macros.cpp

# Макрос UNIQ_ID

Разработать макрос UNIQ_ID, который будет формировать идентификатор, уникальный в пределах данного cpp-файла. Например, следующий код должен компилироваться и работать:  

```c++
int UNIQ_ID = 5;
string UNIQ_ID = "hello!";
```

В рамках данной задачи допускается, что код

```c++
int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке
```

не будет компилироваться.

## Решение
    uniq_id.cpp
