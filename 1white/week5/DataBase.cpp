/*
Необходимо написать программу на С++, которая реализует работу с
простой базой данных (сокращённо «БД»). Программа будет общаться
с пользователем через стандартный ввод и вывод (потоки stdin и stdout).

Будем хранить в нашей БД пары вида: дата, событие. Определим дату 
как строку вида Год-Месяц-День, где Год, Месяц и День — целые числа.

Событие определим как строку из произвольных печатных символов без
разделителей внутри (пробелов, табуляций и пр.). Событие не может 
быть пустой строкой. В одну и ту же дату может произойти много разных 
событий, БД должна суметь их все сохранить. Одинаковые события, 
произошедшие в один и тот же день, сохранять не нужно: достаточно 
сохранить только одно из них.

Наша БД должна понимать определённые команды, чтобы с ней можно было взаимодействовать:
- добавление события:                        Add Дата Событие
- удаление события:                          Del Дата Событие
- удаление всех событий за конкретную дату:  Del Дата
- поиск событий за конкретную дату:          Find Дата
- печать всех событий за все даты:           Print

Все команды, даты и события при вводе разделены пробелами. Команды считываются 
из стандартного ввода. В одной строке может быть ровно одна команда, но можно 
ввести несколько команд в несколько строк. На вход также могут поступать 
пустые строки — их следует игнорировать и продолжать обработку новых команд в последующих строках.

Добавление события (Add Дата Событие)
При добавлении события БД должна его запомнить и затем показывать его 
при поиске (командой Find) или печати (командой Print). Если указанное событие 
для данной даты уже существует, повторное его добавление нужно игнорировать. 
В случае корректного ввода (см. раздел «Обработка ошибок ввода») программа 
ничего не должна выводить на экран.

Удаление события (Del Дата Событие)
Команда должна удалить добавленное ранее событие с указанным именем в 
указанную дату, если оно существует. Если событие найдено и удалено, 
программа должна вывести строку «Deleted successfully» (без кавычек). 
Если событие в указанную дату не найдено, программа должна вывести 
строку «Event not found» (без кавычек).

Удаление нескольких событий (Del Дата)
Команда удаляет все ранее добавленные события за указанную дату. 
Программа всегда должна выводить строку вида «Deleted N events», 
где N — это количество всех найденных и удалённых событий. N может 
быть равно нулю, если в указанную дату не было ни одного события.

Поиск событий (Find Дата)
Найти и распечатать ранее добавленные события в указанную дату. 
Программа должна вывести на печать только сами события, по одному на строке. 
События должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string).

Печать всех событий (Print)
С помощью этой команды можно показать полное содержимое нашей БД. 
Программа должна вывести на печать все пары Дата Событие по одной на строке. 
Все пары должны быть отсортированы по дате, а события в рамках одной 
даты должны быть отсортированы по возрастанию в порядке сравнения 
строк между собой (тип string). Даты должны быть отформатированы 
специальным образом: ГГГГ-ММ-ДД, где Г, М, Д — это цифры чисел года, 
месяца и дня соответственно. Если какое-то число имеет меньше разрядов, 
то оно должно дополняться нулями, например, 0001-01-01 — первое января 
первого года. Вам не понадобится выводить дату с отрицательным значением года.

Обработка ошибок ввода
Ввод в этой задаче не всегда корректен: некоторые ошибки 
ввода ваша программа должна корректно обрабатывать.

Какие ошибки ввода нужно обрабатывать
Если пользователь ввёл неизвестную команду, то программа должна 
об этом сообщить, выведя строку «Unknown command: COMMAND», 
где COMMAND — это та команда, которую ввёл пользователь. 
Командой считается первое слово в строке (до пробела).

Если дата не соответствует формату Год-Месяц-День, 
где Год, Месяц и День — произвольные целые числа, то программа 
должна напечатать «Wrong date format: DATE», где DATE — это то, 
что пользователь ввёл вместо даты (до пробела). Обратите внимание, 
что части даты разделяются ровно одним дефисом, а сама дата не 
должна содержать лишних символов ни перед годом, ни после дня. 
Части даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными.

Если формат даты верен, необходимо проверить валидность месяца и дня.

Если номер месяца не является числом от 1 до 12, выведите 
«Month value is invalid: MONTH», где MONTH — это неверный номер 
месяца, например, 13 или -1.
Если месяц корректен, а день не лежит в диапазоне от 1 до 31, 
выведите «Day value is invalid: DAY», где DAY — это неверный 
номер дня в месяце, например, 39 или 0.
Обратите внимание, что:

Значение года проверять отдельно не нужно.
Не нужно проверять календарную корректность даты: 
количество дней в каждом месяце считается равным 31, високосные года учитывать не нужно.
Если неверны как месяц, так и день, то нужно вывести одно сообщение об ошибке в месяце.
Примеры:

1-1-1 — корректная дата;
-1-1-1 — корректная дата (год -1, месяц 1, день 1);
1--1-1 — дата в верном формате, но с некорректным месяцем -1;
1---1-1 — дата в неверном формате: месяц не может начинаться с двух дефисов.
1​-+1-+1 — корректная дата, так как +1 это целое число
После обработки любой из описанных ошибок ввода и печати сообщения программа 
должна завершать своё выполнение.

Какие ошибки ввода не нужно обрабатывать
Мы не ставим своей целью сломать вашу программу всеми возможными способами, 
поэтому, за исключением описанного в предыдущем пункте, вы можете полагаться 
на корректность ввода. В частности, мы гарантируем, что:

Каждая команда занимает целиком ровно одну строку, хотя во вводе могут 
быть и пустые строки (их нужно игнорировать).
События всегда содержат указанное количество аргументов: после команды Add 
всегда следуют дата и событие, после команды Find всегда следует дата, после 
команды Del всегда следует дата и, возможно, событие, а команда Print 
не содержит дополнительной информации.
Все команды, даты и события являются непустыми строками и не содержат пробелов и 
прочих пробельных символов. (В частности, наши тесты не содержат команды 
«Add 2018-02-12», потому что в ней после даты отсутствует название события.) 
С другой стороны, команда Del может не содержать события после даты: в этом 
случае нужно удалить все события за указанную дату (см. раздел «Удаление нескольких событий»).
Несмотря на то, что дата с отрицательным значением года считается корректной, 
тесты устроены так, что её не понадобится выводить в команде Print.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <cctype>
#include <tuple>

using namespace std;

enum class Request
{
    Empty   = -1,
    Unknown,
    ADD,
    DEL,
    FIND,
    PRINT
};

Request getRequest(const string& req)
{
    if (req.empty())           return Request::Empty;
    if (!req.compare("Add"))   return Request::ADD;
    if (!req.compare("Del"))   return Request::DEL;
    if (!req.compare("Find"))  return Request::FIND;
    if (!req.compare("Print")) return Request::PRINT;

    return Request::Unknown;
}

class Date {
public:
    Date(int year = 1, int month = 1, int day = 1)
    {
        m_year  = year;

        m_month = month;
        if (m_month < 1 || 12 < m_month)
            throw out_of_range("Month value is invalid: " + to_string(m_month));

        m_day   = day;
        if (m_day < 1 || 31 < m_day)
            throw out_of_range("Day value is invalid: " + to_string(m_day));
    }
public:
    int year()  const { return m_year; }
    int month() const { return m_month; }
    int day()   const { return m_day; }

//operators:
public:
    bool operator < (const Date& other) const
    {
        return tie( m_year, m_month, m_day ) < tie(other.m_year, other.m_month, other.m_day);
    }
    bool operator == (const Date& other) const
    {
        return tie(m_year, m_month, m_day) == tie(other.m_year, other.m_month, other.m_day);
    }

    friend ostream& operator<<(ostream& out,const Date& date)
    {
        out
            << setfill('0') << setw(4) << date.year()  << "-"
            << setfill('0') << setw(2) << date.month() << "-"
            << setfill('0') << setw(2) << date.day();   
        return out;
    }
    friend istream& operator>>(istream& in, Date& date)
    {
        in >> date.m_year;
        in.ignore(1);

        in >> date.m_month;

        in.ignore(1);

        in >> date.m_day;

        return in;
    }
private:
    int m_year;
    int m_month;
    int m_day;
};

Date parse(const string& date) {
    istringstream date_stream(date);
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && date_stream.eof();

    if (!ok) {
        throw logic_error("Wrong date format: " + date);
    }
    return Date(year, month, day);
}

class Database {
public:
    void AddEvent   (const Date& date, const string& event)
    {
            database[date].insert(event);
    }

    /*bool DeleteEvent(const Date& date, const string& event)
    {
        if (database.count(date) > 0 && database[date].count(event) > 0) {
            database[date].erase(event);
            return true;
        }
        return false;
    }
    */
    bool DeleteEvent(const Date& date, const string& event)
    {
        if (!database.count(date))
            return false;

        for (auto& [_date, events] : database)
        {
            for (auto& _event : events)
            {
                if (_event == event)
                {
                    database[_date].erase(event);
                    return true;
                }
            }
        }
        return false;
    }
    int  DeleteDate(const Date& date)
    {
        if (database.count(date)) {
            const int event_count = database.at(date).size();
            database.erase(date);
            return event_count;
        }
        return 0;
    }

    void Find(const Date& date) const {
        if (database.count(date)) {
            for (const string& event : database.at(date))
                cout << event << endl;
        }
    }

    void Print() const {
        for (const auto& [date, events] : database) {
            for (const auto& event : events)
                cout << date << " " << event << endl;
        }
    }

private:
    map<Date, set<string>> database;
};

int main() {
    Database db;

    string command;
    try {
        while (getline(cin, command)) {
        
            stringstream ss(command);
            ss >> command;
            Request req = getRequest(command);

            switch (req)
            {
            case Request::Empty: break;
            case Request::Unknown:
                throw logic_error("Unknown command: " + command);
            case Request::ADD:
            {
                Date _date;
                string date;
                ss >> date;
                _date = parse(date);

                string event;
                ss >> event;

                db.AddEvent(_date, event);
            
                event.clear();
                break;
            }
            case Request::DEL:
            {
                Date _date;
                string date;
                ss >> date;
                 _date = parse(date);

                string event;
                ss >> event;
        
                if (event.size())
                {
                    if (db.DeleteEvent(_date, event))
                        cout << "Deleted successfully" << endl;
                    else cout << "Event not found" << endl;
                }
                else
                {
                    int n = db.DeleteDate(_date);
                    cout << "Deleted " << n << " events" << endl;
                }
                break;
            }
            case Request::FIND:
            {
                Date _date;
                string date;
                ss >> date;
                _date = parse(date);

                db.Find(_date);
                break;
            }
            case Request::PRINT: db.Print();
                break;
            default:
                break;
            }
        }
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
        return -1;
    }


    return 0;
}

