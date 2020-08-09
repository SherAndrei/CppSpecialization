/*
–еализуйте справочник столиц стран.

Ќа вход программе поступают следующие запросы:

CHANGE_CAPITAL country new_capital Ч изменение столицы 
страны country на new_capital, либо добавление такой 
страны с такой столицей, если раньше еЄ не было.

RENAME old_country_name new_country_name Ч переименование 
страны из old_country_name в new_country_name.

ABOUT country Ч вывод столицы страны country.

DUMP Ч вывод столиц всех стран.
*/

#include <map>
#include <iostream>
using namespace std;

enum class Request
{
    Unknown = 0,
    CHANGE_CAPITAL,
    RENAME,
    ABOUT,
    DUMP
};

Request getRequest(const string& req)
{
    if (!req.compare("CHANGE_CAPITAL")) return Request::CHANGE_CAPITAL;
    if (!req.compare("RENAME"))         return Request::RENAME;
    if (!req.compare("ABOUT"))          return Request::ABOUT;
    if (!req.compare("DUMP"))           return Request::DUMP;

    return Request::Unknown;
}

int main()
{
    size_t amount;
    cin >> amount;

    map<string, string> directory;

    for (size_t i = 0; i < amount; ++i)
    {
        string request;
        cin >> request;

        Request name = getRequest(request);

        switch (name)
        {
        case Request::Unknown: return -1;
            
        case Request::CHANGE_CAPITAL:
        {
            string country;
            cin >> country;

            string capital;
            cin >> capital;

            if (directory.count(country))
            {
                if (directory[country] != capital)
                {
                    cout << "Country "<< country <<" has changed its capital from "<< directory[country] <<" to " << capital << endl;
                    directory[country] = capital;
                }
                else
                    cout << "Country "<< country <<" hasn't changed its capital" << endl;
            }
            else
            {
                directory[country] = capital;
                cout << "Introduce new country " << country << " with capital " << directory[country] << endl;
            }

            break;
        }
        case Request::RENAME:
        {
            string oldCountry;
            cin >> oldCountry;

            string newCountry;
            cin >> newCountry;

            if (newCountry != oldCountry && directory.count(oldCountry) && !directory.count(newCountry))
            {
                cout << "Country " << oldCountry << " with capital " << directory[oldCountry] << " has been renamed to " << newCountry << endl;
                auto nh = directory.extract(oldCountry);
                nh.key() = newCountry;
                directory.insert(move(nh));
            }
            else
                cout << "Incorrect rename, skip" << endl;

            break;
        }
        case Request::ABOUT:
        {
            string country;
            cin >> country;

            (directory.count(country))
                ? cout << "Country " << country << " has capital " << directory[country] << endl
                : cout << "Country " << country << " doesn't exist" << endl;

            break;
        }
        case Request::DUMP:
        {
            if (!directory.empty())
            {
                for (const auto& [country, capital] : directory)
                {
                    cout << country << "/" << capital << " ";
                }
                cout << endl;
            }
            else
                cout << "There are no countries in the world" << endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

// 6 CHANGE_CAPITAL RussianEmpire Petrograd RENAME RussianEmpire RussianRepublic ABOUT RussianRepublic RENAME RussianRepublic USSR CHANGE_CAPITAL USSR Moscow DUMP
// 24 RENAME FakeCountry FarFarAway ABOUT FarFarAway DUMP CHANGE_CAPITAL TsardomOfRussia Moscow CHANGE_CAPITAL TsardomOfRussia Moscow CHANGE_CAPITAL ColonialBrazil Salvador CHANGE_CAPITAL TsardomOfRussia SaintPetersburg RENAME TsardomOfRussia RussianEmpire CHANGE_CAPITAL RussianEmpire Moscow CHANGE_CAPITAL RussianEmpire SaintPetersburg CHANGE_CAPITAL ColonialBrazil RioDeJaneiro DUMP RENAME ColonialBrazil EmpireOfBrazil ABOUT RussianEmpire RENAME EmpireOfBrazil UnitedStatesOfBrazil CHANGE_CAPITAL RussianEmpire Petrograd RENAME RussianEmpire RussianRepublic RENAME RussianRepublic USSR CHANGE_CAPITAL USSR Moscow CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil ABOUT RussianEmpire DUMP RENAME USSR USSR

/*
    ѕ–»ћ≈– „”∆ќ√ќ  ќƒј:
    #include <iostream>
    #include <string>
    #include <map>

    using namespace std;

    int main() {
      int q;
      cin >> q;

      map<string, string> country_to_capital;

      for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "CHANGE_CAPITAL") {

          string country, new_capital;
          cin >> country >> new_capital;
          if (country_to_capital.count(country) == 0) {
            cout << "Introduce new country " << country << " with capital " << new_capital << endl;
          } else {
            const string& old_capital = country_to_capital[country];
            if (old_capital == new_capital) {
              cout << "Country " << country << " hasn't changed its capital" << endl;
            } else {
              cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
            }
          }
          country_to_capital[country] = new_capital;

        } else if (operation_code == "RENAME") {

          string old_country_name, new_country_name;
          cin >> old_country_name >> new_country_name;
          if (old_country_name == new_country_name || country_to_capital.count(old_country_name) == 0 || country_to_capital.count(new_country_name) == 1) {
            cout << "Incorrect rename, skip" << endl;
          } else {
            cout << "Country " << old_country_name << " with capital " << country_to_capital[old_country_name] <<
                " has been renamed to " << new_country_name << endl;
            country_to_capital[new_country_name] = country_to_capital[old_country_name];
            country_to_capital.erase(old_country_name);
          }

        } else if (operation_code == "ABOUT") {

          string country;
          cin >> country;
          if (country_to_capital.count(country) == 0) {
            cout << "Country " << country << " doesn't exist" << endl;
          } else {
            cout << "Country " << country << " has capital " << country_to_capital[country] << endl;
          }

        } else if (operation_code == "DUMP") {

          if (country_to_capital.empty()) {
            cout << "There are no countries in the world" << endl;
          } else {
            for (const auto& country_item : country_to_capital) {
              cout << country_item.first << "/" << country_item.second << " ";
            }
            cout << endl;
          }

        }

      }

      return 0;
    }

*/