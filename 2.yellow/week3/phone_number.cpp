#include "phone_number.h"
#include <algorithm>
#include <sstream>
#include <tuple>

tuple<string, string, string> parse(const string& international_number) {
    istringstream number_stream(international_number);
    bool ok = true;

    ok = ok && (number_stream.peek() == '+');
    number_stream.ignore(1);

    string country_code;
    ok = ok && getline(number_stream, country_code, '-');

    string city_code;
    ok = ok && getline(number_stream, city_code, '-');

    string local_number;
    ok = ok && getline(number_stream, local_number);

    if (!ok) {
        throw invalid_argument("Wrong number format: " + international_number);
    }
    return make_tuple(country_code, city_code, local_number);
}

//PhoneNumber::PhoneNumber(const string& international_number) {
//    istringstream is(international_number);
//
//    char sign = is.get();
//    getline(is, country_code_, '-');
//    getline(is, city_code_, '-');
//    getline(is, local_number_);
//
//    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
//        throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
//    }
//}

PhoneNumber::PhoneNumber(const string& international_number) {
    tie(country_code_, city_code_, local_number_) = parse(international_number);
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return string("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
