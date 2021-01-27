#include "bus_manager.h"
using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops)
        stops_to_buses[stop].push_back(bus);
}


BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse r;

    if (stops_to_buses.count(stop) == 0) {
        r.response << "No stop";
    } else {
        for (const string& bus : stops_to_buses.at(stop))
            r.response << bus << " ";
    }
    return r;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse r;
    if (buses_to_stops.count(bus) == 0) {
        r.response << "No bus";
    } else {
        for (const string& stop : buses_to_stops.at(bus)) {
            r.response << "Stop " << stop << ": ";
            if (stops_to_buses.at(stop).size() == 1) {
                r.response << "no interchange";
            } else {
                for (const string& other_bus : stops_to_buses.at(stop))
                    if (bus != other_bus)
                        r.response << other_bus << " ";
            }
            if (stop != buses_to_stops.at(bus).back())
                r.response << "\n";
        }
    }
    return r;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse r;

    if (buses_to_stops.empty()) {
        r.response << "No buses";
    } else {
        for (const auto& bus_item : buses_to_stops) {
            r.response << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                r.response << stop << " ";
            }
            r.response << "\n";
        }
    }
    return r;
}
