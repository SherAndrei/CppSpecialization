#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    size_t amount;
    cin >> amount;

    vector<string> vecStr(amount);

    for (auto& item : vecStr)
        cin >> item;
   
    sort(vecStr.begin(), vecStr.end(), 
        [](string& first, string& second) 
            {
            int counter = 0;
            for (size_t i = 0; i < min(first, second).size(); ++i)
            {
                if (tolower(first[i]) == tolower(second[i]))
                    continue;
                if (tolower(first[i]) < tolower(second[i]))
                     return true;
                else return false;
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
  // считываем вектор строк
  int n;
  cin >> n;
  vector<string> v(n);
  for (string& s : v) {
    cin >> s;
  }

  // сортируем
  sort(begin(v), end(v),
       // компаратор дл€ сортировки Ч л€мбда-функци€, сравнивающа€ строки без учЄта регистра
       [](const string& l, const string& r) {
         // сравниваем лексикографически...
         return lexicographical_compare(
             // ... все символы строки l ...
             begin(l), end(l),
             // ... со всеми символами строки r ...
             begin(r), end(r),
             // ..., использу€ в качестве компаратора сравнение отдельных символов без учЄта регистра
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
       }
  );

  // выводим отсортированный вектор
  for (const string& s : v) {
    cout << s << ' ';
  }

  return 0;
}
*/