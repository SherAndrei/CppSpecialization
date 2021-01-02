#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    size_t amount;
    cin >> amount;

    vector<set<string>> busRoutes;
    busRoutes.reserve(amount);

    bool error = false;

    for (size_t i = 0; i < amount; ++i) {
        size_t amountOfStops;
        cin >> amountOfStops;

        set<string> allStops;

        for (size_t j = 0; j < amountOfStops; ++j) {
            string newStop;
            cin >> newStop;

            allStops.insert(newStop);

            newStop.clear();
        }

        for (size_t k = 0; k < busRoutes.size(); ++k) {
            if (busRoutes[k] == allStops) {
                cout << "Already exists for " << k + 1 << endl;
                error = true;
                break;
            }
        }

        if (!error) {
            busRoutes.emplace_back(allStops);
            cout << "New bus " << busRoutes.size() << endl;
        }

        error = false;
        allStops.clear();
    }

    busRoutes.clear();
    return 0;
}

/*
    int main() {
      int q;
      cin >> q;

      map<set<string>, int> buses;

      for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        set<string> stops;
        for (int j = 0; j < n; ++j) {
          string stop;
          cin >> stop;
          stops.insert(stop);
        }
        if (buses.count(stops) == 0) {
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

