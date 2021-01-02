#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

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
        if (!dataForFirstNames.count(year))
            dataForFirstNames[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (!dataForLastNames.count(year))
            dataForLastNames[year] = last_name;
    }
    string GetFullName(int year) {
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
