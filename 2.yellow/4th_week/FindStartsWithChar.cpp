#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt>
FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    auto lower = lower_bound(range_begin, range_end, string(1, prefix));
    auto upper = upper_bound(lower, range_end, string(1, static_cast<char>(prefix + 1)));

    return make_pair(lower, upper);
}

/*
void CharTestEmpty() {
   vector<string> vec;
   auto res = FindStartsWith(begin(vec), end(vec), 'c');
   vec.insert(res.first, "c");
   AssertEqual(vec, vector<string>{ "c" });
}
void SimpleCharTest() {
   {
       vector<string> vec = { "aaa", "aab", "baa", "bba" };

       auto res = FindStartsWith(begin(vec), end(vec), 'a');
       AssertEqual(vector<string>(res.first, res.second), vector<string>{"aaa", "aab"});
   }
   {
       vector<string> vec = { "aaa", "aab", "baa", "bba" };

       auto res = FindStartsWith(begin(vec), end(vec), 'b');
       AssertEqual(vector<string>(res.first, res.second), vector<string>{"baa","bba"});
   }
}
void CharTestNonExisting() {
   {
       vector<string> vec = { "a", "e" };

       auto res = FindStartsWith(begin(vec), end(vec), 'c');
       vec.insert(res.first, "c");
       AssertEqual(vec, vector<string>{ "a", "c", "e" });
   }
   {
       vector<string> vec = { "d", "e" };

       auto res = FindStartsWith(begin(vec), end(vec), 'a');
       vec.insert(res.first, "a");
       AssertEqual(vec, vector<string>{ "a", "d", "e" });
   }
   {
       vector<string> vec = { "d", "e" };

       auto res = FindStartsWith(begin(vec), end(vec), 'z');
       vec.insert(res.first, "z");
       AssertEqual(vec, vector<string>{ "d", "e", "z"});
   }
}
*/
