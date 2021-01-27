#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class QueryType {
    Unknown = -1,
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type = QueryType::Unknown;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);
QueryType getQueryType(const std::string& req);
