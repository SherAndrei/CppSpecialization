#include <map>
#include <vector>
#include <iostream>

using namespace std;

enum class Request {
    Unknown = 0,
    NEW_BUS,
    BUSES_FOR_STOP,
    STOPS_FOR_BUS,
    ALL_BUSES
};


Request getRequest(const string& req) {
    if (!req.compare("NEW_BUS"))        return Request::NEW_BUS;
    if (!req.compare("BUSES_FOR_STOP")) return Request::BUSES_FOR_STOP;
    if (!req.compare("STOPS_FOR_BUS"))  return Request::STOPS_FOR_BUS;
    if (!req.compare("ALL_BUSES"))      return Request::ALL_BUSES;

    return Request::Unknown;
}

int main() {
    size_t amount;
    cin >> amount;

    map<string, vector<string>> busToStops;
    map<string, vector<string>> stopToBuses;

    for (size_t i = 0; i < amount; ++i) {
        string request;
        cin >> request;

        Request name = getRequest(request);

        switch (name) {
        case Request::Unknown: return -1;

        case Request::NEW_BUS: {
            string busName;
            cin >> busName;

            size_t stop_count;
            cin >> stop_count;

            busToStops[busName].reserve(stop_count);

            for (size_t j = 0; j < stop_count; ++j) {
                string newStop;
                cin >> newStop;

                busToStops[busName].emplace_back(newStop);
                stopToBuses[newStop].push_back(busName);
                newStop.clear();
            }

            busName.clear();
            break;
        }
        case Request::BUSES_FOR_STOP: {
            string desiredStop;
            cin >> desiredStop;

            if (stopToBuses.count(desiredStop)) {
                for (const auto& bus : stopToBuses[desiredStop])
                    cout << bus << " ";

                cout << endl;
            } else {
                cout << "No stop" << endl;
            }

            desiredStop.clear();
            break;
        }
        case Request::STOPS_FOR_BUS: {
            string desiredBus;
            cin >> desiredBus;

            string result;

            if (busToStops.count(desiredBus)) {
                for (const auto& stop : busToStops[desiredBus]) {
                    cout << "Stop " << stop << ": ";

                    if (stopToBuses[stop].size() > 1) {
                        for (const auto& bus : stopToBuses[stop]) {
                            if (bus != desiredBus)
                                cout << bus + " ";
                        }
                    } else {
                        cout << "no interchange" << endl;
                    }
                }
            } else {
                cout << "No bus\n";
            }

            desiredBus.clear();
            break;
        }
        case Request::ALL_BUSES: {
            if (!busToStops.empty()) {
                for (const auto& [bus, stops] : busToStops) {
                    cout << "Bus " << bus << ": ";
                    for (const auto& stop : stops)
                        cout << stop << " ";
                    cout << endl;
                }
            } else {
                cout << "No buses" << endl;
            }

            break;
        }
        default:
            break;
        }
    }

    busToStops.clear();
    return 0;
}
