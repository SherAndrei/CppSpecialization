#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};


auto getRank(const Region& reg) {
    return tie(reg.std_name, reg.parent_std_name, reg.names, reg.population);
}

bool operator < (const Region& lhs, const Region& rhs) {
    return getRank(lhs) < getRank(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int result = 0;
    map<Region, int> repetition_count;

    for (const Region& region : regions) {
        result = max(result, ++repetition_count[region]);
    }
    return result;
}


int main() {
    cout << FindMaxRepetitionCount({
       {"Moscow",    "Russia",  {{Lang::DE, "Moskau"  },   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca" }}, 89},
       {"Russia",    "Eurasia", {{Lang::DE, "Russland"},   {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
       {"Moscow",    "Russia",  {{Lang::DE, "Moskau"  },   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca" }}, 89},
       {"Moscow",    "Russia",  {{Lang::DE, "Moskau"  },   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca" }}, 89} })
       << endl;
    cout << FindMaxRepetitionCount({
       {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Russia",
           "Eurasia",
           {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
           89
       }, {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Russia",
           "Eurasia",
           {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
           89
       },
       }) << endl;

    cout << FindMaxRepetitionCount({
       {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Russia",
           "Eurasia",
           {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
           89
       }, {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Moscow",
           "Toulouse",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           89
       }, {
           "Moscow",
           "Russia",
           {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
           31
       },
       }) << endl;

    return 0;
}
