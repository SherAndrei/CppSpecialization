#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include <numeric>

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

class Rational {
 public:
  Rational();
  Rational(int numerator, int denominator);

  int Numerator() const;
  int Denominator() const;
};

void TestDefaultConstructor() {
    AssertEqual(Rational().Numerator(),   Rational(0, 1).Numerator());
    AssertEqual(Rational().Denominator(), Rational(0, 1).Denominator());
}

void TestConstructorForPositive() {
    mt19937 gen;
    uniform_int_distribution<> unif(1, 100);

    for (auto i = 0; i < 50; ++i) {
        auto a = unif(gen);

        AssertEqual(Rational(a, a).Numerator(),   Rational(1, 1).Numerator());
        AssertEqual(Rational(a, a).Denominator(), Rational(1, 1).Denominator());

        AssertEqual(Rational(a * a, a).Numerator(),   Rational(a, 1).Numerator());
        AssertEqual(Rational(a * a, a).Denominator(), Rational(a, 1).Denominator());

        AssertEqual(Rational(a, a * a).Numerator(),   Rational(1, a).Numerator());
        AssertEqual(Rational(a, a * a).Denominator(), Rational(1, a).Denominator());

        AssertEqual(Rational(a + a, a * a).Numerator(),   Rational(2, a).Numerator());
        AssertEqual(Rational(a + a, a * a).Denominator(), Rational(2, a).Denominator());

        AssertEqual(Rational(a * a, a + a).Numerator(),   Rational(a, 2).Numerator());
        AssertEqual(Rational(a * a, a + a).Denominator(), Rational(a, 2).Denominator());
    }
}

void TestConstructorForNegative() {
    mt19937 gen;
    uniform_int_distribution<> unif(-100, -1);

    for (auto i = 0; i < 50; ++i) {
        auto a = unif(gen);

        AssertEqual(Rational(a, a).Numerator(),   Rational(1, 1).Numerator());
        AssertEqual(Rational(a, a).Denominator(), Rational(1, 1).Denominator());

        AssertEqual(Rational(a * a, a).Numerator(),   Rational(a, 1).Numerator());
        AssertEqual(Rational(a * a, a).Denominator(), Rational(a, 1).Denominator());

        AssertEqual(Rational(a, a * a).Numerator(),   Rational(-1, -a).Numerator());
        AssertEqual(Rational(a, a * a).Denominator(), Rational(-1, -a).Denominator());

        AssertEqual(Rational(a + a, a * a).Numerator(),   Rational(-2, -a).Numerator());
        AssertEqual(Rational(a + a, a * a).Denominator(), Rational(-2, -a).Denominator());

        AssertEqual(Rational(a * a, a + a).Numerator(),   Rational(a, 2).Numerator());
        AssertEqual(Rational(a * a, a + a).Denominator(), Rational(a, 2).Denominator());
    }
}
void TestConstuctorForZeroNumerator() {
    mt19937 gen;
    uniform_int_distribution<> unif(-10, 10);

    for (auto i = 0; i < 10; ++i) {
        auto a = unif(gen);
        if (a != 0) {
            AssertEqual(Rational(0, a).Numerator(),   Rational(0, 1).Numerator());
            AssertEqual(Rational(0, a).Denominator(), Rational(0, 1).Denominator());
        }
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestConstructorForPositive, "TestConstuctorForPositive");
    runner.RunTest(TestConstructorForNegative, "TestConstructorForNegative");
    runner.RunTest(TestConstuctorForZeroNumerator, "TestConstuctorForZeroNumerator");

    return 0;
}
