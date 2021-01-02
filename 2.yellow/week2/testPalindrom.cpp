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

void Assert(bool b, const string& hint = {}) {
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


bool IsPalindrom(const string& str) {
//    cout << "|" << str << "|" << endl;
    for (size_t i = 0; i < str.size() / 2; i++)
        if (str[i] != str[str.size() - i - 1])
            return false;
    return true;
}

void TestVoid() {
    Assert(IsPalindrom(""));
}

void TestOneSymbol() {
    for (char i = -128; i != 127; ++i)
        Assert(IsPalindrom(string(1, i)));
}

void TestTwoSymbols() {
    for (char i = -128, j = 127; i != 127 && j != -128 ; ++i && --j)
        (i == j)
            ? AssertEqual(IsPalindrom(string(string(1, i) + string(1, j))), true)
            : AssertEqual(IsPalindrom(string(string(1, i) + string(1, j))), false);
}

void TestSpaces() {
    for (char i = -128; i != 127; ++i) {
        Assert(IsPalindrom(string(" " + string(1, i) + " ")));
        Assert(IsPalindrom(string(string(1, i) +" "+ string(1, i))));
    }
}

void TestFirstAndLastSymbols() {
    for (char i = -128, j = 127; i != 127 && j != -128 ; ++i && --j)
        (i == j)
            ? AssertEqual(IsPalindrom(string(string(1, i) + string(2, j))), true)
            : AssertEqual(IsPalindrom(string(string(1, i) + string(2, j))), false);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestVoid, "TestVoid");
    runner.RunTest(TestOneSymbol, "TestOneSymbol");
    runner.RunTest(TestTwoSymbols, "TestTwoSymbols");
    runner.RunTest(TestSpaces, "TestSpaces");
    runner.RunTest(TestFirstAndLastSymbols, "TestFirstAndLastSymbols");
    return 0;
}
