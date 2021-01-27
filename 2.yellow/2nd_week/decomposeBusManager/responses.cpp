#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
    return os << r.response.str();
}
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
    return os << r.response.str();
}
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
    return os << r.response.str();
}
