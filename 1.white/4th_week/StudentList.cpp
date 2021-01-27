#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

enum class Request {
    Unknown = 0,
    Name,
    Date
};


Request getRequest(const string& req) {
    if (!req.compare("name")) return Request::Name;
    if (!req.compare("date")) return Request::Date;

    return Request::Unknown;
}

struct Student {
    string firstName;
    string lastName;
    int day = 0;
    int month = 0;
    int year = 0;
};


bool checkInt(int number, int min, int max) {
    return (min <= number && number <= max);
}

int main() {
    int amountOfStudents, amountOfRequests;
    cin >> amountOfStudents;

    if (!checkInt(amountOfStudents, 0, 10'000)) {
        cout << "bad result" << endl;
        return -1;
    }

    vector<Student> data(amountOfStudents);

    for (auto& student : data) {
        cin >> student.firstName;
        cin >> student.lastName;
        cin >> student.day;
        cin >> student.month;
        cin >> student.year;
        if (!checkInt(student.day, 0, 1000000000) &&
            !checkInt(student.month, 0, 1000000000) &&
            !checkInt(student.year, 0, 1000000000)) {
            cout << "bad result" << endl;
            return -1;
        }
    }

    cin >> amountOfRequests;
    if (!checkInt(amountOfRequests, 0, 10'000)) {
        cout << "bad result" << endl;
        return -1;
    }

    for (int i = 0; i < amountOfRequests; i++) {
        string req;
        cin >> req;

        Request another = getRequest(req);

        switch (another) {
        case Request::Unknown:  {
            int err;
            cin >> err;
            cout << "bad request" << endl;
            continue;
        }
        case Request::Name:  {
            int num;
            cin >> num;

            if (!checkInt(num, 1, amountOfStudents)) {
                cout << "bad request" << endl;
                continue;
            }

            cout << data[num - 1].firstName << " " << data[num - 1].lastName << endl;
            break;
        }
        case Request::Date: {
            int num;
            cin >> num;

            if (!checkInt(num, 1, amountOfStudents)) {
                cout << "bad request" << endl;
                continue;
            }

            cout << data[num - 1].day << "." << data[num - 1].month << "." << data[num - 1].year << endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

//3 Ivan Ivanov 1 1 1901 Petr Petrox 2 2 1902 Alexander Sidorov 3 3 1903 3 name 1 date 3 mark 5
