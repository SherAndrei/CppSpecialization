#include "test_runner.h"
#include "airline_ticket.h"

#include <tuple>
#include <iomanip>
#include <sstream>
using namespace std;

#define DATE_OPERATOR(x)                                                          \
bool operator x (Date lhs, Date rhs)                                              \ {                                                                                 \
    return tie(lhs.year, lhs.month, lhs.day) x tie(rhs.year, rhs.month, rhs.day); \
}

DATE_OPERATOR(< );
DATE_OPERATOR(== );
DATE_OPERATOR(!= );

istream& operator >> (istream& in, Date& date) {
    in >> date.year;
    in.ignore(1);
    in >> date.month;
    in.ignore(1);
    in >> date.day;
    return in;
}
ostream& operator << (ostream& out, Date date) {
    out
        << setfill('0') << setw(4) << date.year << "-"
        << setfill('0') << setw(2) << date.month << "-"
        << setfill('0') << setw(2) << date.day;
    return out;
}


#define TIME_OPERATOR(x)                                                          \
bool operator x (Time lhs, Time rhs)                                              \ {                                                                                 \
    return tie(lhs.hours, lhs.minutes) x tie(rhs.hours, rhs.minutes);             \
}

TIME_OPERATOR(< );
TIME_OPERATOR(== );
TIME_OPERATOR(!= );

ostream& operator << (ostream& out, Time time) {
    out
        << setfill('0') << setw(2) << time.hours << ":"
        << setfill('0') << setw(2) << time.minutes;
    return out;
}

istream& operator >> (istream& in, Time& time) {
    in >> time.hours;
    in.ignore(1);
    in >> time.minutes;
    return in;
}
#define UPDATE_FIELD(ticket, field, updates) \ {                                            \
    auto it = updates.find(#field);          \
    if (it != updates.end()){                \
        istringstream is(it->second);        \
        is >> ticket.field;                  \
    }                                        \
}


void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
    };


    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };

    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 �� �������� ������ "departure_date" � "departure_time", �������
    // �������� ���� ����� �� ������ ����������
    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
