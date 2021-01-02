#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


string reverseToString(const vector<string>& newVec) {
    string result;
    int size = (int)newVec.size();

    for (int i = size - 1; i >= 0; --i) {
        if (i == size - 1) {
            result = (newVec[i]);
            continue;
        }

        if (i == size - 2)
            result += (" (");

        result += newVec[i];

        if (i != 0)
            result += ", ";
        else
            result += ")";
    }
    return result;
}

string getLast(const map<int, string>& names, int year) {
    string name;

    for (const auto& item : names) {
        if (item.first <= year) {
            name = item.second;
        } else {
            break;
        }
    }

    return name;
}

string getLastHistory(const map<int, string>& names, int year) {
    vector<string> vec;

    for (const auto& [m_year, name] : names) {
        if (m_year <= year) {
                vec.push_back(name);
        } else {
            break;
        }
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
  for (const auto& item : names_by_year) {
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  if (names.empty()) {
    return "";
  }
  reverse(begin(names), end(names));

  string joined_name = names[0];

  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      joined_name += " (";
    } else {
      joined_name += ", ";
    }
    joined_name += names[i];
  }

  if (names.size() > 1) {
    joined_name += ")";
  }
  return joined_name;
}

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
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

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
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
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

