# Наследование своими руками

Дан следующий код:

```cpp
#include <iostream>

using namespace std;

class Animal {
public:
    // ваш код

    const string Name;
};

class Dog {
public:
    // ваш код

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};
```

Определите до конца тела классов, соблюдая следующие требования:

1. Класс Dog должен являться наследником класса Animal.
2. Конструктор класса Dog должен принимать параметр типа string и инициализировать им поле Name в классе Animal.

### Решение
 SimpleInheritance.cpp

# Отправка уведомлений

В этой задаче вам нужно разработать классы SmsNotifier и EmailNotifier, отправляющие уведомления в виде SMS и e-mail соответственно, а также абстрактный базовый класс для них.

Вам даны функции SendSms и SendEmail, которые моделируют отправку SMS и e-mail.

```cpp
void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);
```

Разработайте: 

1. Абстрактный базовый класс INotifier, у которого будет один чисто виртуальный метод void Notify(const string& message).
2. Класс SmsNotifier, который:
    * является потомком класса INotifier;
    * в конструкторе принимает один параметр типа string — номер телефона;
    * переопределяет метод Notify и вызывает из него функцию SendSms.
3. Класс EmailNotifier, который:
    * является потомком класса INotifier;
    * в конструкторе принимает один параметр типа string — адрес электронной почты;
    * переопределяет метод Notify и вызывает из него функцию SendEmail.

### Решение
 SmsAndEmailNotifier.cpp

# Набор фигур

Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур:  

```cpp
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
```

Как видно из кода, есть два вида команд: 
* ADD — добавить фигуру в набор;
* PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.

Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:
* ADD RECT width height —  добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
* ADD TRIANGLE a b c —  добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
* ADD CIRCLE r —  добавить круг радиуса r (например, ADD CIRCLE 5).

Не меняя функцию main, реализуйте недостающие функции и классы:
* базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
* классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
* функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

Гарантируется, что размеры всех фигур — это натуральные числа не больше 1000. В качестве значения PI используйте 3,14.

### Решение
 Figure.cpp
