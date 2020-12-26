#include "database.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if (set_db[date].insert(event).second)
        vec_db[date].push_back(event);
}

//bool Database::DeleteEvent(const Date& date, const string& event)
//{
//    if (db.count(date))
//        return db[date].erase(event) > 0;
//    return false;
//    //if (Database.count(date) > 0 && Database[date].count(event) > 0) {
//    //    Database[date].erase(event);
//    //    return true;
//    //}
//    //return false;
//}
//
//int Database::DeleteDate(const Date& date)
//{
//    if (db.count(date)) {
//        const int event_count = db.at(date).size();
//        db.erase(date);
//        return event_count;
//    }
//    else return 0;
//}
//
//void Database::Find(const Date& date) const
//{
//    if (db.count(date)) {
//        for (const string& event : db.at(date))
//            cout << event << endl;
//    }
//}

vector<string> Database::Findif (function<bool(Date, string)> pred) const {
    vector<string> result;
    //vec_db
    for (const auto& [date, events] : vec_db)
        for (const auto& event : events)
            if (pred(date, event))
                result.push_back(Entry(date, event));

    return result;
}

int Database::Removeif (function<bool(Date, string)> pred) {
    size_t result = 0;
    vector<Date> for_erase;
    for (auto& entry : vec_db) {
        auto iter = stable_partition(entry.second.begin(), entry.second.end(),
            [&](const string& event) { return !pred(entry.first, event); });

        for (auto it = iter; it != entry.second.end(); ++it) {
            set_db.at(entry.first).erase(*it);
            result++;
        }
        iter = entry.second.erase(iter, entry.second.end());

        if (iter == entry.second.begin()) {
            for_erase.push_back(entry.first);
        }
    }
    for (const auto& date : for_erase) {
        set_db.erase(date);
        vec_db.erase(date);
    }

    return static_cast<int>(result);
}

string Database::Last(const Date& date) const {
    auto iter_after = vec_db.upper_bound(date);

    if (iter_after != vec_db.begin())
        if (!(prev(iter_after))->second.empty())
            return Entry(prev(iter_after)->first,*((prev(iter_after))->second).rbegin());

    throw invalid_argument("aaaaaa");
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events] : vec_db) {
        for (const auto& event : events)
            os << Entry(date, event) << endl;
    }
}

string Database::Entry(const Date& date, const string& event) const {
    return date.to_string() + " " + event;
}
