#pragma once
#include <sstream>

struct BusesForStopResponse {
    std::stringstream response;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    std::stringstream response;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::stringstream response;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
