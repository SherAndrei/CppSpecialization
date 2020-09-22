#include <exception>
#include <sstream>
#include <iomanip>
#include "date.h"

using namespace std;

Date::Date(int year, int month, int day)
{
    m_year = year;

    m_month = month;
    if (m_month < 1 || 12 < m_month)
        throw out_of_range("Month value is invalid: " + std::to_string(m_month));

    m_day = day;
    if (m_day < 1 || 31 < m_day)
        throw out_of_range("Day value is invalid: " + std::to_string(m_day));
}

int Date::year() const
{
    return m_year;
}

int Date::month() const
{
    return m_month;
}

int Date::day() const
{
    return m_day;
}

string Date::to_string() const
{
    ostringstream os;
    os << *this;
    return os.str();
}

bool Date::operator==(const Date& other) const
{
    return tie(m_year, m_month, m_day) == tie(other.m_year, other.m_month, other.m_day);
}

bool Date::operator!=(const Date& other) const
{
    return !(*this == other);
}

bool Date::operator<(const Date& other) const
{
    return tie(m_year, m_month, m_day) < tie(other.m_year, other.m_month, other.m_day);
}

bool Date::operator>(const Date& other) const
{
    return other < *this;
}

bool Date::operator<=(const Date& other) const
{
    return !(other < *this);
}

bool Date::operator>=(const Date& other) const
{
    return !(*this < other);
}

Date Date::operator=(const Date& other)
{
    if (*this != other)
    {
        this->m_year  = other.m_year;
        this->m_month = other.m_month;
        this->m_day   = other.m_day;
    }
    return *this;

}

ostream& operator<<(ostream& out, const Date& date)
{
    out
        << setfill('0') << setw(4) << date.year() << "-"
        << setfill('0') << setw(2) << date.month() << "-"
        << setfill('0') << setw(2) << date.day();
    return out;
}

Date ParseDate(istream& is)
{
    string my_date;
    is >> my_date;
    istringstream date_stream(my_date);
    
    bool ok = true;

    int year = -1;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month = -1;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day = -1;
    ok = ok && (date_stream >> day);
    //ok = ok && date_stream.eof();

    if (!ok) {
        throw logic_error("Wrong date format: " + date_stream.str());
    }
    return Date(year, month, day);
}
