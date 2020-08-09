#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    Unknown = -1,
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

QueryType getQueryType(const string& req)
{
    if (!req.compare("NEW_BUS"))        return QueryType::NewBus;
    if (!req.compare("BUSES_FOR_STOP")) return QueryType::BusesForStop;
    if (!req.compare("STOPS_FOR_BUS"))  return QueryType::StopsForBus;
    if (!req.compare("ALL_BUSES"))      return QueryType::AllBuses;

    return QueryType::Unknown;
}

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string req;
    is >> req;

    q.type = getQueryType(req);

    switch (q.type)
    {
    case QueryType::NewBus:
    {
        int stop_count;
        is >> q.bus >> stop_count;

        q.stops.resize(stop_count);
        for (auto& stop : q.stops)
            is >> stop;

        break;
    }
    case QueryType::BusesForStop:
        is >> q.stop;
        break;
    case QueryType::StopsForBus:
        is >> q.bus;
        break;
    case QueryType::AllBuses:
        break;
    default:
        break;
    }

    return is;
}

struct BusesForStopResponse {
    stringstream response;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    return os << r.response.str();
}

struct StopsForBusResponse {
    stringstream response;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    return os << r.response.str();
}

struct AllBusesResponse {
    stringstream response;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    return os << r.response.str();
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops)
            stops_to_buses[stop].push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const 
    {
        BusesForStopResponse r;

        if (stops_to_buses.count(stop) == 0) 
            r.response << "No stop";
        else {
            for (const string& bus : stops_to_buses.at(stop)) 
                r.response << bus << " ";
        }
        return r;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const
    {
        StopsForBusResponse r;
        if (buses_to_stops.count(bus) == 0) {
            r.response << "No bus";
        }
        else {
            for (const string& stop : buses_to_stops.at(bus)) 
            {
                r.response << "Stop " << stop << ": ";
                if (stops_to_buses.at(stop).size() == 1) 
                    r.response << "no interchange";
                else {
                    for (const string& other_bus : stops_to_buses.at(stop)) 
                        if (bus != other_bus) 
                            r.response << other_bus << " ";
                }
                if(stop != buses_to_stops.at(bus).back())
                r.response << "\n";
            }
        }
        return r;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse r;

        if (buses_to_stops.empty()) {
            r.response << "No buses";
        }
        else {
            for (const auto& bus_item : buses_to_stops) {
                r.response << "Bus " << bus_item.first << ": ";
                for (const string& stop : bus_item.second) 
                {
                    r.response << stop << " ";
                }
                r.response << "\n";
            }
        }
        return r;
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
/*
10 ALL_BUSES BUSES_FOR_STOP Marushkino STOPS_FOR_BUS 32K NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo BUSES_FOR_STOP Vnukovo NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo STOPS_FOR_BUS 272 ALL_BUSES

6 ALL_BUSES BUSES_FOR_STOP Marushkino STOPS_FOR_BUS 32K NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo BUSES_FOR_STOP Vnukovo

*/

