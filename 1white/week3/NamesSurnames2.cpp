/*
В отличие от метода GetFullName, метод GetFullNameWithHistory 
должен вернуть не только последние имя и фамилию к концу данного 
года, но ещё и все предыдущие имена и фамилии в 
обратном хронологическом порядке. 
Если текущие факты говорят о том, что человек два раза подряд изменил 
фамилию или имя на одно и то же, второе изменение при формировании
истории нужно игнорировать.
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


string reverseToString(const vector<string>& newVec)
{
    string result;
    int size = (int)newVec.size();

    for (int i = size - 1; i >= 0; --i)
    {

        if (i == size - 1)
        {
            result = (newVec[i]);
            continue;
        }

        if (i == size - 2)
            result += (" (");

        result += newVec[i];

        if (i != 0)
            result += ", ";
        else result += ")";
    }
    return result;
}

string getLast(const map<int, string>& names, int year) {
    string name;  // изначально имя неизвестно

    for (const auto& item : names) {
        if (item.first <= year) {
            name = item.second;
        }
        else {
            break;
        }
    }

    return name;
}

string getLastHistory(const map<int, string>& names, int year) {
    
    vector<string> vec;

    for (const auto& [m_year,name] : names) {
        if (m_year <= year) {
                vec.push_back(name);
        }
        else break;
    }

    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    return reverseToString(vec);
}

class Person{
public:
    void ChangeFirstName(int year, const string& first_name) {
            yearToFirstName[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
            yearToLastName[year] = last_name;
    }

    string GetFullName(int year) {
        string firstName = getLast(yearToFirstName, year);
        string lastName = getLast(yearToLastName, year);

        if (firstName.empty() && lastName.empty())
            return "Incognito";

        if (firstName.empty())
            return lastName + " with unknown first name";

        if (lastName.empty())
            return firstName + " with unknown last name";

        return firstName + " " + lastName;
    }

    string GetFullNameWithHistory(int year) {   

        string firstName = getLastHistory(yearToFirstName, year);
        string lastName  = getLastHistory(yearToLastName, year);

        if (firstName.empty() && lastName.empty())
            return "Incognito";

        if (firstName.empty())
            return lastName + " with unknown first name";
        
        if (lastName.empty())
            return firstName + " with unknown last name";
    
        return firstName + " " + lastName;
    }

private:
    map<int, string> yearToFirstName;
    map<int, string> yearToLastName;
};


/*
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  // перебираем всю историю в хронологическом порядке
  for (const auto& item : names_by_year) {
    // если очередное имя не относится к будущему и отличается от предыдущего,
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      // добавляем его в историю
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  // нет истории — имя неизвестно
  if (names.empty()) {
    return "";
  }
  // меняем прямой хронологический порядок на обратный
  reverse(begin(names), end(names));

  // начинаем строить полное имя с самого последнего
  string joined_name = names[0];

  // перебираем все последующие имена
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      // если это первое «историческое» имя, отделяем его от последнего скобкой
      joined_name += " (";
    } else {
      // если это не первое имя, отделяем от предыдущего запятой
      joined_name += ", ";
    }
    // и добавляем очередное имя
    joined_name += names[i];
  }

  // если в истории было больше одного имени, мы открывали скобку — закроем её
  if (names.size() > 1) {
    joined_name += ")";
  }
  // имя со всей историей готово
  return joined_name;
}

// см. решение предыдущей задачи
string BuildFullName(const string& first_name, const string& last_name) {
  if (first_name.empty() && last_name.empty()) {
    return "Incognito";
  } else if (first_name.empty()) {
    return last_name + " with unknown first name";
  } else if (last_name.empty()) {
    return first_name + " with unknown last name";
  } else {
    return first_name + " " + last_name;
  }
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    // найдём историю изменений имени и фамилии
    // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) {
    // получим полное имя со всей историей
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    // получим полную фамилию со всей историей
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    // объединим их с помощью готовой функции
    return BuildFullName(first_name, last_name);
  }

private:
  vector<string> FindFirstNamesHistory(int year) {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) {
    return FindNamesHistory(last_names, year);
  }

  map<int, string> first_names;
  map<int, string> last_names;
};

*/