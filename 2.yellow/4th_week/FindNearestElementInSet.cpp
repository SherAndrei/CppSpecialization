#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto [less_eq, greater] = numbers.equal_range(border);

    if (less_eq == numbers.begin())
        return less_eq;

    auto less = prev(less_eq);

    if (less_eq == numbers.end())
        return less;

    return (
            (border - *less <= *less_eq - border)
                ? less
                : less_eq);
}

/*
void TestEmpty() {
   set<int> numbers;
   Assert(FindNearestElement(numbers, 1) == numbers.end());
}

void TestSizeOne() {
   {
       set<int> numbers = { 1 };

       AssertEqual(*FindNearestElement(numbers, 1), 1);
       AssertEqual(*FindNearestElement(numbers, 0), 1);
       AssertEqual(*FindNearestElement(numbers, 50), 1);
   }
}
void Test() {
   {
       set<int> numbers = { 1, 10, 100 };

       AssertEqual(*FindNearestElement(numbers, 10), 10);
       AssertEqual(*FindNearestElement(numbers,  0), 1);
       AssertEqual(*FindNearestElement(numbers, 50), 10);
   }
   {
       set<int> numbers = { -100, 100 };

       AssertEqual(*FindNearestElement(numbers, 0), -100);
   }
}

*/
