#include <iostream>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <memory>

#include "tests.h"
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"

using namespace std;

Date ParseDate(istream& is);

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const Date   date  = ParseDate(is);
            const string event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            shared_ptr<Node>             condition = ParseCondition(is);
            function<bool(Date, string)> predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            int count = db.Removeif(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            shared_ptr<Node>             condition = ParseCondition(is);
            function<bool(Date, string)> predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };


            const auto entries = db.Findif(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}
