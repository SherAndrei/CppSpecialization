/*
–еализуйте систему хранени€ автобусных маршрутов. ¬ам нужно обрабатывать следующие запросы:

NEW_BUS bus stop_count stop1 stop2 ... Ч добавить маршрут 
автобуса с названием bus и stop_count остановками с названи€ми stop1, stop2, ...

BUSES_FOR_STOP stop Ч вывести названи€ всех маршрутов автобуса, 
проход€щих через остановку stop.

STOPS_FOR_BUS bus Ч вывести названи€ всех остановок маршрута bus со 
списком автобусов, на которые можно пересесть на каждой из остановок.

ALL_BUSES Ч вывести список всех маршрутов с остановками.

*/

#include <map>
#include <vector>
#include <iostream>

using namespace std;

enum class Request
{
    Unknown = 0,
    NEW_BUS,
    BUSES_FOR_STOP,
    STOPS_FOR_BUS,
    ALL_BUSES
};

Request getRequest(const string& req)
{
    if (!req.compare("NEW_BUS"))        return Request::NEW_BUS;
    if (!req.compare("BUSES_FOR_STOP")) return Request::BUSES_FOR_STOP;
    if (!req.compare("STOPS_FOR_BUS"))  return Request::STOPS_FOR_BUS;
    if (!req.compare("ALL_BUSES"))      return Request::ALL_BUSES;

    return Request::Unknown;
}

int main()
{
    size_t amount;
    cin >> amount;

    map<string, vector<string>> busToStops;
    map<string, vector<string>> stopToBuses;

    for (size_t i = 0; i < amount; ++i)
    {
        string request;
        cin >> request;
        

        Request name = getRequest(request);

        switch (name)
        {
        case Request::Unknown: return -1;

        case Request::NEW_BUS:
        {
            string busName;
            cin >> busName;

            size_t stop_count;
            cin >> stop_count;

            busToStops[busName].reserve(stop_count);

            for (size_t j = 0; j < stop_count; ++j)
            {
                string newStop;
                cin >> newStop;

                busToStops[busName].emplace_back(newStop);
                stopToBuses[newStop].push_back(busName);
                
                newStop.clear();
            }

            busName.clear();
            break;
        }
        case Request::BUSES_FOR_STOP:
        {
            string desiredStop;
            cin >> desiredStop;

            if (stopToBuses.count(desiredStop))
            {
                for(const auto& bus : stopToBuses[desiredStop])
                    cout << bus << " ";

                cout << endl;
            }
            else
                cout << "No stop" << endl;
            
            desiredStop.clear();
            break;
        }
        case Request::STOPS_FOR_BUS:
        {
            string desiredBus;
            cin >> desiredBus;

            string result;

            if (busToStops.count(desiredBus))
            {
                for (const auto& stop : busToStops[desiredBus])
                {
                    cout << "Stop " << stop << ": ";

                    if (stopToBuses[stop].size() > 1)
                    {
                        for (const auto& bus : stopToBuses[stop])
                        {
                            if (bus != desiredBus)
                                cout << bus + " ";
                        }
                    }
                    else 
                        cout << "no interchange" << endl;
                } 
            }
            else
                cout << "No bus\n";

            desiredBus.clear();
            break;
        }
        case Request::ALL_BUSES:
        {
            if (!busToStops.empty())
                for (const auto& [bus, stops] : busToStops)
                {
                    cout << "Bus " << bus << ": ";
                    for (const auto& stop : stops)
                        cout << stop << " ";
                    cout << endl;
                }
            else
                cout << "No buses" << endl;

            break;
        }
        default:
            break;
        }
    }

    busToStops.clear();
    return 0;
}

//  5 NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo  NEW_BUS 32K 5 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo ALL_BUSES
//  4 NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo  NEW_BUS 32K 5 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo BUSES_FOR_STOP Vnukovo ALL_BUSES
// 10 ALL_BUSES BUSES_FOR_STOP Marushkino STOPS_FOR_BUS 32K NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo BUSES_FOR_STOP Vnukovo NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo STOPS_FOR_BUS 272 ALL_BUSES
// 9 NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo STOPS_FOR_BUS 272 STOPS_FOR_BUS 950 BUSES_FOR_STOP Marushkino BUSES_FOR_STOP Vnukovo BUSES_FOR_STOP Solntsevo
