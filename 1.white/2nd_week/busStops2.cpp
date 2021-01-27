#include <map>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    size_t amount;
    cin >> amount;

    vector<string> busRoutes;
    busRoutes.reserve(amount);

    bool error = false;

    for (size_t i = 0; i < amount; ++i) {
        size_t amountOfStops;
        cin >> amountOfStops;

        string allStops;

        for (size_t j = 0; j < amountOfStops; ++j) {
            string newStop;
            cin >> newStop;

            allStops += newStop + " ";

            newStop.clear();
        }

        for (size_t k = 0; k < busRoutes.size(); ++k) {
            if (!busRoutes[k].compare(allStops)) {
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

      map<vector<string>, int> buses;

      for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        vector<string> stops(n);
        for (string& stop : stops) {
          cin >> stop;
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

