#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Request {
    Unknown = 0,
    ADD,
    DUMP,
    NEXT
};


Request getRequest(const string& req) {
    if (!req.compare("ADD"))  return Request::ADD;
    if (!req.compare("DUMP")) return Request::DUMP;
    if (!req.compare("NEXT")) return Request::NEXT;

    return Request::Unknown;
}

void PrintVec(const vector<string>& vec) {
    for (auto var : vec) {
        cout << var << " | ";
    }
}

int main() {
    vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int monthIdx = 0;

    vector<string> toDoList(daysInMonth[monthIdx]);

    int Q;
    cin >> Q;

    string str;

    for (int i = 0; i < Q; i++) {
        monthIdx = monthIdx % 12;

        cin >> str;
        Request another = getRequest(str);

        switch (another) {
        case Request::Unknown: return -1;

        case Request::ADD: {
            int idx;
            cin >> idx;

            if (idx > daysInMonth[monthIdx])
                return -1;

            string other;
            cin >> other;

            toDoList[idx - 1] += other + " ";

            break;
        }
        case Request::DUMP: {
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
        case Request::NEXT: {
            int nextMonthIdx    = (monthIdx + 1) % 12;

            if (daysInMonth[monthIdx] > daysInMonth[nextMonthIdx]) {

                int diff = daysInMonth[monthIdx] - daysInMonth[nextMonthIdx];

                for (int j = diff; j >= 1; --j) {
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
    #include <iostream>
    #include <string>
    #include <vector>

    using namespace std;

    const vector<int> MONTH_LENGTHS =
      {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    const int MONTH_COUNT = MONTH_LENGTHS.size();

    int main() {
      int q;
      cin >> q;

      int month = 0;

      vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

      for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {

          int day;
          string concern;
          cin >> day >> concern;
          --day;
          days_concerns[day].push_back(concern);

        } else if (operation_code == "NEXT") {

          const int old_month_length = MONTH_LENGTHS[month];

          month = (month + 1) % MONTH_COUNT;

          const int new_month_length = MONTH_LENGTHS[month];

          if (new_month_length < old_month_length) {

            vector<string>& last_day_concerns = days_concerns[new_month_length - 1];

            for (int day = new_month_length; day < old_month_length; ++day) {
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

