#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
 public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

 private:
    int fail_count = 0;
};

class Person {
 public:
  void ChangeFirstName(int year, const string& first_name);
  void ChangeLastName(int year, const string& last_name);
  string GetFullName(int year);
};

void TestIncognito() {
    {
        Person person;
        AssertEqual("Incognito", person.GetFullName(1));
    }
    {
        Person person;
        person.ChangeFirstName(2, "first_name_in_2_year");
        person.ChangeLastName(2, "last_name_in_2_year");

        AssertEqual("Incognito", person.GetFullName(1));
    }
    {
        Person person;
        person.ChangeFirstName(2, "first_name_in_2_year");

        AssertEqual("Incognito", person.GetFullName(1));
    }
    {
        Person person;
        person.ChangeLastName(2, "last_name_in_2_year");

        AssertEqual("Incognito", person.GetFullName(1));
    }
}

void TestFirstName() {
    {
        Person person;
        person.ChangeFirstName(0, "firstname0");
        person.ChangeFirstName(1, "firstname1");
        person.ChangeFirstName(2, "firstname2");


        AssertEqual("firstname0 with unknown last name", person.GetFullName(0));
        AssertEqual("firstname1 with unknown last name", person.GetFullName(1));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(2));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeFirstName(2, "firstname2");
        person.ChangeFirstName(1, "firstname1");
        person.ChangeFirstName(0, "firstname0");


        AssertEqual("firstname0 with unknown last name", person.GetFullName(0));
        AssertEqual("firstname1 with unknown last name", person.GetFullName(1));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(2));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeFirstName(0, "firstname0");
        person.ChangeFirstName(2, "firstname2");
        person.ChangeFirstName(1, "firstname1");


        AssertEqual("firstname0 with unknown last name", person.GetFullName(0));
        AssertEqual("firstname1 with unknown last name", person.GetFullName(1));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(2));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeFirstName(1, "firstname1");
        person.ChangeFirstName(0, "firstname0");
        person.ChangeFirstName(2, "firstname2");


        AssertEqual("firstname0 with unknown last name", person.GetFullName(0));
        AssertEqual("firstname1 with unknown last name", person.GetFullName(1));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(2));
        AssertEqual("firstname2 with unknown last name", person.GetFullName(5));
    }
}
void TestLastName() { {
        Person person;
        person.ChangeLastName(0, "lastname0");
        person.ChangeLastName(1, "lastname1");
        person.ChangeLastName(2, "lastname2");


        AssertEqual("lastname0 with unknown first name", person.GetFullName(0));
        AssertEqual("lastname1 with unknown first name", person.GetFullName(1));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(2));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeLastName(2, "lastname2");
        person.ChangeLastName(1, "lastname1");
        person.ChangeLastName(0, "lastname0");


        AssertEqual("lastname0 with unknown first name", person.GetFullName(0));
        AssertEqual("lastname1 with unknown first name", person.GetFullName(1));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(2));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeLastName(0, "lastname0");
        person.ChangeLastName(2, "lastname2");
        person.ChangeLastName(1, "lastname1");


        AssertEqual("lastname0 with unknown first name", person.GetFullName(0));
        AssertEqual("lastname1 with unknown first name", person.GetFullName(1));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(2));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(5));
    }
    {
        Person person;
        person.ChangeLastName(1, "lastname1");
        person.ChangeLastName(0, "lastname0");
        person.ChangeLastName(2, "lastname2");


        AssertEqual("lastname0 with unknown first name", person.GetFullName(0));
        AssertEqual("lastname1 with unknown first name", person.GetFullName(1));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(2));
        AssertEqual("lastname2 with unknown first name", person.GetFullName(5));
    }
}
void TestFullName() { {
        Person person;
        person.ChangeFirstName(1, "firstname1");
        person.ChangeLastName(1, "lastname1");

        AssertEqual(person.GetFullName(1), "firstname1 lastname1");
        AssertEqual(person.GetFullName(2), "firstname1 lastname1");
    }
    {
        Person person;
        person.ChangeFirstName(1, "firstname1");
        person.ChangeLastName(2, "lastname2");

        AssertEqual(person.GetFullName(2), "firstname1 lastname2");
        AssertEqual(person.GetFullName(3), "firstname1 lastname2");
    }
    {
        Person person;
        person.ChangeFirstName(2, "firstname2");
        person.ChangeLastName(1, "lastname1");

        AssertEqual(person.GetFullName(2), "firstname2 lastname1");
        AssertEqual(person.GetFullName(3), "firstname2 lastname1");
    }
}
void TestIfIsThereOnlyOneChangeInYear() { {
        Person person;

        person.ChangeFirstName(1, "first_name1");
        person.ChangeFirstName(1, "first_name2");
        AssertEqual("first_name2 with unknown last name", person.GetFullName(1));
    }
    {
        Person person;

        person.ChangeLastName(1, "last_name1");
        person.ChangeLastName(1, "last_name2");
        AssertEqual("last_name2 with unknown first name", person.GetFullName(1));
    }
    {
        Person person;

        person.ChangeFirstName(1, "first_name1");
        person.ChangeFirstName(1, "first_name2");
        person.ChangeLastName(1, "last_name1");
        person.ChangeLastName(1, "last_name2");
        AssertEqual("first_name2 last_name2", person.GetFullName(1));
    }
}


void TestPredefinedLastNameFirst() {
    Person person;

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeFirstName(1967, "Polina");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
}

void TestPredefined() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

    person.ChangeFirstName(1969, "Appolinaria");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1969), "Appolinaria Sergeeva");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1968, "Volkova");
    AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1968), "Polina Volkova");
    AssertEqual(person.GetFullName(1969), "Appolinaria Volkova");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestFirstName, "TestFirstName");
    runner.RunTest(TestLastName, "TestLastName");
    runner.RunTest(TestFullName, "TestFullName");
    runner.RunTest(TestIfIsThereOnlyOneChangeInYear, "TestIfIsThereOnlyOneChangeInYear");

    return 0;
}
