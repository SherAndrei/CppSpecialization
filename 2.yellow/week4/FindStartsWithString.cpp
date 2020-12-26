#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace std;

//#include "../../Utilities/UnitTestFrameWork.hpp"

template<typename It>
void PrintRange (It begin, It end) {
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}


template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto lower = lower_bound(range_begin, range_end, prefix);
 
    if (prefix.empty())
        return make_pair(lower, lower);
    auto upper = find_if (lower, range_end, [&](const string& str) { return str.compare(0, prefix.size(), prefix) != 0; });

    return make_pair(lower, upper);
}

//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(
//    RandomIt range_begin, RandomIt range_end, string prefix) {
//
//    // ��� ������, ������������ � prefix, ������ ��� ����� ������ "<prefix>"
//    auto left = lower_bound(range_begin, range_end, prefix);
//
//    // �������� ������, ������� � ������ ��������� ����� ��������
//    // ������ ������� ������ ��������� �����, ������������ � prefix
//    string upper_bound = prefix;
//    ++upper_bound[upper_bound.size() - 1];
//
//    // ������ ����������� �����, �� ������� upper_bound,
//    // ����������� �������� ������ �������������
//    auto right = lower_bound(range_begin, range_end, upper_bound);
//
//    return { left, right };

//}
//void TestEmpty()
//{
//    {
//        vector<string> vec;
//        auto res = FindStartsWith(begin(vec), end(vec), "abc");
//        vec.insert(res.first, "abc");
//        AssertEqual(vec, vector<string>{ "abc" });
//    }
//    {
//        vector<string> vec = { "aaa", "aab" };

//        auto res = FindStartsWith(begin(vec), end(vec), {});
//        vec.insert(res.first, string{});
//        AssertEqual(vec, vector<string>{ "", "aaa", "aab"});
//    }
// }
//void Test()
//{
//    {
//        vector<string> vec = { "aaa", "aab", "baa", "bba" };

//        auto res = FindStartsWith(begin(vec), end(vec), "aa");
//        AssertEqual(vector<string>(res.first, res.second), vector<string>{"aaa", "aab"});
//    }
//    {
//        vector<string> vec = { "aaa", "aab", "baa", "bba" };

//        auto res = FindStartsWith(begin(vec), end(vec), "bb");
//        AssertEqual(vector<string>(res.first, res.second), vector<string>{ "bba"});
//    }
//}
//void TestNonExisting()
//{
//    {
//        vector<string> vec = { "aaa", "eee" };

//        auto res = FindStartsWith(begin(vec), end(vec), "abc");
//        vec.insert(res.first, "abc");
//        AssertEqual(vec, vector<string>{ "aaa", "abc", "eee" });
//    }
//    {
//        vector<string> vec = { "ddd", "eee" };

//        auto res = FindStartsWith(begin(vec), end(vec), "aaa");
//        vec.insert(res.first, "aaa");
//        AssertEqual(vec, vector<string>{ "aaa", "ddd", "eee" });
//    }
//    {
//        vector<string> vec = { "ddd", "eee" };

//        auto res = FindStartsWith(begin(vec), end(vec), "zzz");
//        vec.insert(res.first, "zzz");
//        AssertEqual(vec, vector<string>{ "ddd", "eee", "zzz"});
//    }
//}
//void TestBadSize()
//{
//    vector<string> vec = { "aa", "ab" };

//    auto res = FindStartsWith(begin(vec), end(vec), "aaa");
//    vec.insert(res.first, "aaa");
//    AssertEqual(vec, vector<string>{ "aa", "aaa", "ab"});
//}
//void TestConsequtive()
//{
//    vector<string> vec = { "aa", "ab" };

// 
//    auto res = FindStartsWith(begin(vec), end(vec), "aaa");
//    vec.insert(res.first, "aaa");
//    AssertEqual(vec, vector<string>{ "aa", "aaa", "ab"});
// 
//    res = FindStartsWith(begin(vec), end(vec), "aaa");
//    vec.insert(res.first, "aaa");
//    AssertEqual(vec, vector<string>{ "aa", "aaa", "aaa", "ab"});
//
//    res = FindStartsWith(begin(vec), end(vec), "aa");
//    AssertEqual(vector<string>(res.first, res.second), vector<string>{ "aa", "aaa", "aaa"});
//}
//int main()
//{
//    TestRunner r;
//    r.RunTest(TestEmpty, "TestEmpty");
//    r.RunTest(Test, "Test");
//    r.RunTest(TestNonExisting, "TestNonExisting");
//    r.RunTest(TestBadSize, "TestBadSize");
//    r.RunTest(TestConsequtive, "TestConsequtive");
//}

