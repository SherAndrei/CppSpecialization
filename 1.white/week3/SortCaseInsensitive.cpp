#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    size_t amount;
    cin >> amount;

    vector<string> vecStr(amount);

    for (auto& item : vecStr)
        cin >> item;

    sort(vecStr.begin(), vecStr.end(),
        [](string& first, string& second)  {
            int counter = 0;
            for (size_t i = 0; i < min(first, second).size(); ++i) {
                if (tolower(first[i]) == tolower(second[i]))
                    continue;
                if (tolower(first[i]) < tolower(second[i]))
                     return true;
                else
                    return false;
            }
            }
        );

    for (auto& item : vecStr)
        cout << item << " ";

    return 0;
}

/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  // ��������� ������ �����
  int n;
  cin >> n;
  vector<string> v(n);
  for (string& s : v) {
    cin >> s;
  }

  // ���������
  sort(begin(v), end(v),
       // ���������� ��� ���������� � ������-�������, ������������ ������ ��� ����� ��������
       [](const string& l, const string& r) {
         // ���������� �����������������...
         return lexicographical_compare(
             // ... ��� ������� ������ l ...
             begin(l), end(l),
             // ... �� ����� ��������� ������ r ...
             begin(r), end(r),
             // ..., ��������� � �������� ����������� ��������� ��������� �������� ��� ����� ��������
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
       }
  );

  // ������� ��������������� ������
  for (const string& s : v) {
    cout << s << ' ';
  }

  return 0;
}
*/
