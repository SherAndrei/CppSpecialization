#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <cctype>
#include <tuple>

using namespace std;

enum class Request {
    Empty   = -1,
    Unknown,
    ADD,
    DEL,
    FIND,
    PRINT
};


Request getRequest(const string& req) {
    if (req.empty())           return Request::Empty;
    if (!req.compare("Add"))   return Request::ADD;
    if (!req.compare("Del"))   return Request::DEL;
    if (!req.compare("Find"))  return Request::FIND;
    if (!req.compare("Print")) return Request::PRINT;

    return Request::Unknown;
}

class Date {
 public:
    explicit Date(int year = 1, int month = 1, int day = 1) {
        m_year  = year;

        m_month = month;
        if (m_month < 1 || 12 < m_month)
            throw out_of_range("Month value is invalid: " + to_string(m_month));

        m_day   = day;
        if (m_day < 1 || 31 < m_day)
            throw out_of_range("Day value is invalid: " + to_string(m_day));
    }

 public:
    int year()  const { return m_year; }
    int month() const { return m_month; }
    int day()   const { return m_day; }

// operators:
 public:
    bool operator < (const Date& other) const {
        return tie( m_year, m_month, m_day ) < tie(other.m_year, other.m_month, other.m_day);
    }
    bool operator == (const Date& other) const {
        return tie(m_year, m_month, m_day) == tie(other.m_year, other.m_month, other.m_day);
    }

    friend ostream& operator<<(ostream& out, const Date& date) {
        out
            << setfill('0') << setw(4) << date.year()  << "-"
            << setfill('0') << setw(2) << date.month() << "-"
            << setfill('0') << setw(2) << date.day();
        return out;
    }
    friend istream& operator>>(istream& in, Date& date) {
        in >> date.m_year;
        in.ignore(1);

        in >> date.m_month;

        in.ignore(1);

        in >> date.m_day;

        return in;
    }

 private:
    int m_year;
    int m_month;
    int m_day;
};


Date parse(const string& date) {
    istringstream date_stream(date);
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && date_stream.eof();

    if (!ok) {
        throw logic_error("Wrong date format: " + date);
    }
    return Date(year, month, day);
}

class Database {
 public:
    void AddEvent(const Date& date, const string& event) {
            database[date].insert(event);
    }

    /*bool DeleteEvent(const Date& date, const string& event) {
        if (database.count(date) > 0 && database[date].count(event) > 0) {
            database[date].erase(event);
            return true;
        }
        return false;
    }
    */

    bool DeleteEvent(const Date& date, const string& event) {
        if (!database.count(date))
            return false;

        for (auto& [_date, events] : database) {
            for (auto& _event : events) {
                if (_event == event) {
                    database[_date].erase(event);
                    return true;
                }
            }
        }
        return false;
    }
    int  DeleteDate(const Date& date) {
        if (database.count(date)) {
            const int event_count = database.at(date).size();
            database.erase(date);
            return event_count;
        }
        return 0;
    }

    void Find(const Date& date) const {
        if (database.count(date)) {
            for (const string& event : database.at(date))
                cout << event << endl;
        }
    }

    void Print() const {
        for (const auto& [date, events] : database) {
            for (const auto& event : events)
                cout << date << " " << event << endl;
        }
    }

 private:
    map<Date, set<string>> database;
};


int main() {
    Database db;

    string command;
    try {
        while (getline(cin, command)) {
            stringstream ss(command);
            ss >> command;
            Request req = getRequest(command);

            switch (req) {
            case Request::Empty: break;
            case Request::Unknown:
                throw logic_error("Unknown command: " + command);
            case Request::ADD: {
                Date _date;
                string date;
                ss >> date;
                _date = parse(date);

                string event;
                ss >> event;

                db.AddEvent(_date, event);

                event.clear();
                break;
            }
            case Request::DEL: {
                Date _date;
                string date;
                ss >> date;
                 _date = parse(date);

                string event;
                ss >> event;

                if (event.size()) {
                    if (db.DeleteEvent(_date, event))
                        cout << "Deleted successfully" << endl;
                    else
                        cout << "Event not found" << endl;
                } else {
                    int n = db.DeleteDate(_date);
                    cout << "Deleted " << n << " events" << endl;
                }
                break;
            }
            case Request::FIND: {
                Date _date;
                string date;
                ss >> date;
                _date = parse(date);

                db.Find(_date);
                break;
            }
            case Request::PRINT: db.Print();
                break;
            default:
                break;
            }
        }
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
        return -1;
    }


    return 0;
}

