#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

#include "test_runner.h"

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first,
    ForwardIterator last, UnaryPredicate pred) {
    ForwardIterator max_pos = first = find_if(first, last, pred);
    for (; first != last; first = find_if(++first, last, pred)) {
        max_pos = *max_pos < *first ? first : max_pos;
    }
    return max_pos;
}

void Test() {
    auto IsEven = [](int x) {
        return x % 2 == 0;
    };
    {
        vector<int> v = { 1, 20, 3, 4, 10 };

        ASSERT(*max_element_if(v.begin(), v.end(), IsEven) == 20);
    }
    {
        vector<int> v = { };

        ASSERT(max_element_if(v.begin(), v.end(), IsEven) == v.end());
        ASSERT(max_element_if(v.begin(), v.end(), IsEven) == v.begin());
    }
    {
        vector<int> v = { 1 };

        ASSERT(max_element_if(v.begin(), v.end(), IsEven) == v.end());
    }
}

void TestUniqueMax() {
    auto IsEven = [](int x) {
        return x % 2 == 0;
    };
    {
        vector<int> numbers(10);
        iota(numbers.begin(), numbers.end(), 1);

        Assert(max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
              "Expect the last element");
    } {
        const list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };

        auto max_iterator = hill.begin();
        advance(max_iterator, 2);
        Assert(max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
               "Expect the maximal even number");
    }
}

void TestSeveralMax() {
    struct IsCapitalized {
        bool operator()(const string& s) {
            return !s.empty() && isupper(s.front());
        }
    };

    const forward_list<string> text{ "One", "two", "Three", "One", "Two",
      "Three", "one", "Two", "three" };

    auto max_iterator = text.begin();
    advance(max_iterator, 4);

    Assert(max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
           "Expect the first \"Two\"");
}

void TestNoMax() {
    const vector<int> empty;
    const string str = "Non-empty string";

    auto AlwaysTrue = [](int) {
        return true;
    };

    Assert(max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
          "Expect end for empty container");

    auto AlwaysFalse = [](char) {
        return false;
    };

    Assert(max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
           "Expect end for AlwaysFalse predicate");
}

int main() {
    TestRunner tr;
    tr.RunTest(Test, "Test");
    tr.RunTest(TestUniqueMax, "TestUniqueMax");
    tr.RunTest(TestSeveralMax, "TestSeveralMax");
    tr.RunTest(TestNoMax, "TestNoMax");
    return 0;
}
