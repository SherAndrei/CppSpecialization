#include <iostream>
#include <vector>

using namespace std;

enum class Request {
    Unknown = 0,
    COME = 1,
    WORRY,
    QUIET,
    WORRY_COUNT
};



Request getRequest(const string& req) {
    if (!req.compare("COME"))  return Request::COME;
    if (!req.compare("WORRY")) return Request::WORRY;
    if (!req.compare("QUIET")) return Request::QUIET;
    if (!req.compare("WORRY_COUNT")) return Request::WORRY_COUNT;

    return Request::Unknown;
}

void PrintVec(const vector<bool>& vec) {
    for (auto var : vec) {
        cout << var << " | ";
    }
}

/*
    ��������� ������ �� ��������� ��������, ������������ �����
    ���� 1, �� ������� ���������
    ���� 0, �� �������
*/

int main() {
    vector<bool> queue;

    int Q;
    cin >> Q;

    string str;

    for (int i = 0; i < Q; i++) {
        cin >> str;
        Request another = getRequest(str);

        switch (another) {
        case Request::Unknown: return -1;

        case Request::COME: {
            int amount;
            cin >> amount;
            if (amount >= 0) {
                for (int j = 0; j < amount; j++)
                    queue.push_back(false);
            } else {
                for (int j = 0; j < -amount; j++)
                    queue.pop_back();
            }

            break;
        }
        case Request::WORRY: {
            int idx;
            cin >> idx;

            queue[idx] = true;

            break;
        }
        case Request::QUIET: {
            int idx;
            cin >> idx;

            queue[idx] = false;

            break;
        }
        case Request::WORRY_COUNT: {
            int counter = 0;
            for (bool var : queue) {
                if (var == true)
                    counter++;
            }
            cout << counter << endl;
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
    #include <algorithm>

    using namespace std;

    int main() {
      int q;
      cin >> q;
      vector<bool> is_nervous;

      for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "WORRY_COUNT") {

          cout << count(begin(is_nervous), end(is_nervous), true) << endl;

        } else {
          if (operation_code == "WORRY" || operation_code == "QUIET") {

            int person_index;
            cin >> person_index;

            is_nervous[person_index] = (operation_code == "WORRY");

          } else if (operation_code == "COME") {

            int person_count;
            cin >> person_count;

            is_nervous.resize(is_nervous.size() + person_count, false);

          }
        }
      }

      return 0;
    }

*/

