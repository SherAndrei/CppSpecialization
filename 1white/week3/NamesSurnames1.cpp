/*
Реализуйте класс для человека, поддерживающий 
историю изменений человеком своих фамилии и имени.

Считайте, что в каждый год может произойти не более 
одного изменения фамилии и не более одного изменения
имени. При этом с течением времени могут открываться
всё новые факты из прошлого человека, поэтому года́ в
последовательных вызовах методов ChangeLastName и 
ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна 
содержать разделённые одним пробелом имя и фамилию 
человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения 
фамилии и имени, верните строку "Incognito".
Если к данному году случилось изменение фамилии, но 
не было ни одного изменения имени, верните "last_name 
with unknown first name".
Если к данному году случилось изменение имени, но не 
было ни одного изменения фамилии, верните "first_name 
with unknown last name".
*/
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

string getLast(map<int, string>& data, int year)
{
    auto i = data.begin();

    if (year < i->first)
        return {};

    int resultYear = 0;
    while (i != data.end() && i->first <= year)
    {
        resultYear = i->first;
        i++;
    }

    return data[resultYear];
}

class Person{
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

//Без итераторов!:
/*
string getLast(const map<int, string>& names, int year) {
    string name;  // изначально имя неизвестно

    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto& item : names) {
        // если очередной год не больше данного, обновляем имя
        if (item.first <= year) {
            name = item.second;
        }
        else {
            // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
            break;
        }
    }

    return name;
}
*/