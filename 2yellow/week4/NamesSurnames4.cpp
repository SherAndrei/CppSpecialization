#include <iostream>
#include <map>   
#include <iterator>
#include <algorithm>

using namespace std;

//#include "../../Utilities/UnitTestFrameWork.hpp"

template<typename It>
void PrintRange (It begin, It end)
{
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}

string getLast(const map<int, string>& names, int year) {
    auto iter_after = names.upper_bound(year);
    string name;
    if (iter_after != names.begin()) {
        name = (--iter_after)->second;
    }
    return name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        if (!dataForFirstNames.count(year))
            dataForFirstNames[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        if (!dataForLastNames.count(year))
            dataForLastNames[year] = last_name;
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year

        string firstName = getLast(dataForFirstNames, year);
        string lastName  = getLast(dataForLastNames, year);

        if (firstName.empty() && lastName.empty())
            return "Incognito";

        if (firstName.empty())
            return lastName + " with unknown first name";

        if (lastName.empty())
            return firstName + " with unknown last name";

        return firstName + " " + lastName;
    }

private:
    map<int, string> dataForFirstNames;
    map<int, string> dataForLastNames;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}