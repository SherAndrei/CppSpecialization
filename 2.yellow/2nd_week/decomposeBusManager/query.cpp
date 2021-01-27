#include "query.h"
using namespace std;

QueryType getQueryType(const string& req) {
    if (!req.compare("NEW_BUS"))        return QueryType::NewBus;
    if (!req.compare("BUSES_FOR_STOP")) return QueryType::BusesForStop;
    if (!req.compare("STOPS_FOR_BUS"))  return QueryType::StopsForBus;
    if (!req.compare("ALL_BUSES"))      return QueryType::AllBuses;

    return QueryType::Unknown;
}

std::istream& operator >> (std::istream& is, Query& q) {
    string req;
    is >> req;

    q.type = getQueryType(req);

    switch (q.type) {
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
