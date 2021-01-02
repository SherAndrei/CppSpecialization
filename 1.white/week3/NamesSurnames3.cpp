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

class Person {
 public:
    Person(const string& firstName, const string& lastName, int birthYear) {
        m_birth_year = birthYear;
        yearToFirstName[m_birth_year] = firstName;
        yearToLastName[m_birth_year]  = lastName;
    }

    void ChangeFirstName(int year, const string& first_name) {
        yearToFirstName[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        yearToLastName[year] = last_name;
    }

    string GetFullName(int year) const {
        if (year < m_birth_year)
            return "No person";

        string firstName = getLast(yearToFirstName, year);
        string lastName  = getLast(yearToLastName, year);

        if (firstName.empty() && lastName.empty())
            return "Incognito";

        if (firstName.empty())
            return lastName + " with unknown first name";

        if (lastName.empty())
            return firstName + " with unknown last name";

        return firstName + " " + lastName;
    }

    string GetFullNameWithHistory(int year) const {
        if (year < m_birth_year)
            return "No person";

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
    int m_birth_year = 0;
};


int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
