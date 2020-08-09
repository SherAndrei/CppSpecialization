/*
    У каждого из нас есть повторяющиеся ежемесячные дела, 
    каждое из которых нужно выполнять в конкретный день каждого месяца: 
    оплата счетов за электричество, абонентская плата за связь и пр. 
    Вам нужно реализовать работу со списком таких дел на месяц, а именно, 
    реализовать набор следующих операций:

    ADD i s
    Назначить дело с названием s на день i текущего месяца.

    DUMP i
    Вывести все дела, запланированные на день i текущего месяца.

    NEXT
    Перейти к списку дел на новый месяц. 
    При выполнении данной команды вместо текущего (старого) 
    списка дел на текущий месяц создаётся и становится активным (новый) 
    список дел на следующий месяц: все дела со старого списка 
    дел копируются в новый список. После выполнения данной 
    команды новый список дел и следующий месяц становятся текущими, 
    а работа со старым списком дел прекращается. При переходе к 
    новому месяцу необходимо обратить внимание на разное количество 
    дней в месяцах:

        если следующий месяц имеет больше дней, чем текущий, 
        «дополнительные» дни необходимо оставить пустыми (не содержащими дел);

        если следующий месяц имеет меньше дней, чем текущий, 
        дела со всех «лишних» дней необходимо переместить на последний день следующего месяца.

    Замечания
        Историю списков дел хранить не требуется, работа ведется только с 
        текущим списком дел текущего месяца. Более того, при создании списка дел 
        на следующий месяц, он «перетирает» предыдущий список.

        Обратите внимание, что количество команд NEXT в общей последовательности
        команд при работе со списком дел может превышать 11.

        Начальным текущим месяцем считается январь.

        Количества дней в месяцах соответствуют Григорианскому 
        календарю с той лишь разницей, что в феврале всегда 28 дней.

    Примеры:

         5 ADD 5 Salary ADD 5 Walk ADD 5 WalkPreparations DUMP 5 DUMP 30
         12 ADD 5 Salary ADD 31 Walk ADD 30 WalkPreparations NEXT DUMP 5 DUMP 28 NEXT DUMP 31 DUMP 30 DUMP 28 ADD 28 Payment DUMP 28
         15 NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT ADD 31 Oct_31 NEXT NEXT NEXT NEXT DUMP 28
         29 ADD 31 Jan_1 NEXT ADD 28 Feb NEXT ADD 31 Mar NEXT ADD 30 Apr NEXT ADD 31 May NEXT ADD 30 Jun NEXT ADD 31 Jul NEXT ADD 31 Aug NEXT ADD 30 Sep NEXT ADD 31 Oct NEXT ADD 30 Nov NEXT ADD 31 Dec NEXT ADD 31 Jan_2 DUMP 27 DUMP 28 DUMP 30 DUMP 31
         30 ADD 1 Jan_1_1 ADD 31 Jan_31_1 NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT NEXT DUMP 1 DUMP 28 DUMP 30 DUMP 31
         11 ADD 27 abc ADD 28 def ADD 29 ghj ADD 30 qwe ADD 31 iow NEXT DUMP 27 DUMP 28 DUMP 29 DUMP 30 DUMP 31
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Request
{
    Unknown = 0,
    ADD,
    DUMP,
    NEXT
};

Request getRequest(const string& req)
{
    if (!req.compare("ADD"))  return Request::ADD;
    if (!req.compare("DUMP")) return Request::DUMP;
    if (!req.compare("NEXT")) return Request::NEXT;
    
    return Request::Unknown;
}

void PrintVec(const vector<string>& vec)
{
    for (auto var : vec)
    {
        cout << var << " | ";
    }
}

int main()
{
    vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int monthIdx = 0;

    vector<string> toDoList(daysInMonth[monthIdx]);

    int Q;
    cin >> Q;

    string str;

    for (int i = 0; i < Q; i++)
    {
        monthIdx = monthIdx % 12;

        cin >> str;
        Request another = getRequest(str);

        switch (another)
        {
        case Request::Unknown: return -1;
            
        case Request::ADD:
        {
            int idx;
            cin >> idx;

            if (idx > daysInMonth[monthIdx])
                return -1;

            string other;
            cin >> other;

            toDoList[idx - 1] += other + " ";

            break;
        }
        case Request::DUMP:
        {
            int idx;
            cin >> idx;


            if (idx > daysInMonth[monthIdx])
                 cout << "0" << endl;
            else
                 cout
                     << count(toDoList[idx - 1].begin(), toDoList[idx - 1].end(), ' ')
                     << " "
                     << toDoList[idx - 1] << endl;

            break;
        }
        case Request::NEXT:
        {
            int nextMonthIdx    = (monthIdx + 1) % 12;

            if (daysInMonth[monthIdx] > daysInMonth[nextMonthIdx])
            {

                int diff = daysInMonth[monthIdx] - daysInMonth[nextMonthIdx];

                for (int j = diff; j >= 1; --j)
                {
                    toDoList[daysInMonth[nextMonthIdx] - 1] +=
                        toDoList[daysInMonth[monthIdx] - j];
                    toDoList[daysInMonth[monthIdx] - j].clear();
                }

            }

            toDoList.resize(daysInMonth[nextMonthIdx]);

            //toDoList.clear();
            monthIdx++;

            break;
        }
        default:
            break;
        }
    }

    return 0;
}
      


/*
    ПРИМЕР ЧУЖОГО КОДА:
    #include <iostream>
    #include <string>
    #include <vector>

    using namespace std;

    // глобальные (доступные во всей программе) константы
    // часто принято называть ЗАГЛАВНЫМИ_БУКВАМИ
    const vector<int> MONTH_LENGTHS =
      {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int MONTH_COUNT = MONTH_LENGTHS.size();

    int main() {
      int q;
      cin >> q;

      // номер текущего месяца (от 0 до 11)
      int month = 0;

      // внешний вектор должен иметь длину, равную количеству дней в первом месяце;
      // все внутренние векторы по умолчанию пусты, потому что дел изначально нет
      vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

      for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {

          int day;
          string concern;
          cin >> day >> concern;
          --day;  // элементы вектора нумеруются с нуля
          days_concerns[day].push_back(concern);

        } else if (operation_code == "NEXT") {

          // перед переходом к следующему месяцу запомним длину предыдущего
          // обьявляем эту переменную константной, потому что менять её не планируем
          const int old_month_length = MONTH_LENGTHS[month];

          // номер месяца должен увеличиться на 1, но после декабря идёт январь:
          // например, (5 + 1) % 12 = 6, но (11 + 1) % 12 = 0
          month = (month + 1) % MONTH_COUNT;

          const int new_month_length = MONTH_LENGTHS[month];

          // если новый месяц больше предыдущего, достаточно сделать resize;
          // иначе перед resize надо переместить дела с «лишних» последних дней
          if (new_month_length < old_month_length) {

            // далее понадобится добавлять новые дела в последний день нового месяца
            // чтобы не писать несколько раз days_concerns[new_month_length - 1],
            // создадим ссылку с более коротким названием для этого вектора
            vector<string>& last_day_concerns = days_concerns[new_month_length - 1];

            // перебираем все «лишние» дни в конце месяца
            for (int day = new_month_length; day < old_month_length; ++day) {
              // копируем вектор days_concerns[day]
              // в конец вектора last_day_concerns
              last_day_concerns.insert(
                  end(last_day_concerns),
                  begin(days_concerns[day]), end(days_concerns[day]));
            }
          }
          days_concerns.resize(new_month_length);

        } else if (operation_code == "DUMP") {

          int day;
          cin >> day;
          --day;

          // выводим список дел в конкретный день в нужном формате
          cout << days_concerns[day].size() << " ";
          for (const string& concern : days_concerns[day]) {
            cout << concern << " ";
          }
          cout << endl;

        }
      }

      return 0;
    }
*/