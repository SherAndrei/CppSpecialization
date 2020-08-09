#include <map>
#include <vector>
#include <iostream>
//#include "Timer.hpp"
using namespace std;

int main()
{
    size_t amount;
    cin >> amount;
//    Timer timer;

    vector<string> busRoutes;
    busRoutes.reserve(amount);

    bool error = false;

    for (size_t i = 0; i < amount; ++i)
    {
        size_t amountOfStops;
        cin >> amountOfStops;

        string allStops;

        for (size_t j = 0; j < amountOfStops; ++j)
        {
            string newStop;
            cin >> newStop;

            allStops += newStop + " ";
        
            newStop.clear();
        }

        for (size_t k = 0; k < busRoutes.size(); ++k)
        {
            if (!busRoutes[k].compare(allStops))
            {
                cout << "Already exists for " << k + 1 << endl;
                error = true;
                break;
            }
        }

        if (!error)
        {
            busRoutes.emplace_back(allStops);
            cout << "New bus " << busRoutes.size() << endl;
        }

        error = false;
        allStops.clear();
    }

    busRoutes.clear();
    return 0;
}

//6 11 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Kokoshkino 11 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Kokoshkino  11 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Kokoshkino  1 Kokoshkino 2 Marushkino Kokoshkino 11 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Kokoshkino 
//8 2 A B 2 A B 2 A B 2 A B 4 A B C A 4 A B C A 4 A B C A 4 A B A C
//5 2 A B 2 A B 2 A B 2 A B 2 A B
//5 2 A B 2 A B 2 A B 2 A B 2 A B

/*
    
    ПРИМЕР ЧУЖОГО КОДА:
    int main() {
      int q;
      cin >> q;

      map<vector<string>, int> buses;

      for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        vector<string> stops(n);
        for (string& stop : stops) {
          cin >> stop;
        }

        // проверяем, не существует ли уже маршрут с таким набором остановок
        if (buses.count(stops) == 0) {

          // если не существует, нужно сохранить новый маршрут;
          // его номер на единицу больше текущего количества маршрутов
          const int new_number = buses.size() + 1;
          buses[stops] = new_number;
          cout << "New bus " << new_number << endl;

        } else {
          cout << "Already exists for " << buses[stops] << endl;
        }
      }

      return 0;
    }
*/