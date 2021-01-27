#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include "date.h"

using namespace std;

class Database {
 public:
    void Add(const Date& date, const string& event);
    vector<string> Findif(function<bool(Date, string)> pred) const;
    int            Removeif(function<bool(Date, string)> pred);
    string         Last(const Date& date) const;
    void           Print(ostream& os)      const;
    string         Entry(const Date& date, const string& event) const;

 private:
    map<Date, set<string>>    set_db;
    map<Date, vector<string>> vec_db;
};
