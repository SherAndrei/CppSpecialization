#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

//#include "..\..\Utilities\UnitTestFrameWork.hpp"

template <typename T>
void RemoveDuplicates(vector<T>& elements);

template<typename It>
void PrintRange (It begin, It end) {
    for (auto it = begin; it != end; ++it)
        cout << *it << " / ";
    cout << endl;
}

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    sort(begin(elements), end(elements));
    elements.erase(unique(begin(elements), end(elements)), end(elements));
}

//void Test()
//{
//    vector<int> vec;
//    auto vbeg = begin(vec);
//    auto vend = end(vec);
//    {
//        RemoveDuplicates(vec);
//        AssertEqual(vec, vector<int>{});
//    }
//    {
//        vec = {1,1};

//        RemoveDuplicates(vec);
//        Assert(is_permutation(vbeg, vend, begin(vector<int>{1})));
//    }
//    {
//        vec = { 1,2,1 };

//        RemoveDuplicates(vec);
//        Assert(is_permutation(vbeg, vend, begin(vector<int>{1,2})));
//    }
//    {
//        vec = { 1,1,2 };

//        RemoveDuplicates(vec);
//        Assert(is_permutation(vbeg, vend, begin(vector<int>{1, 2})));
//    }
//    {
//        vec = { 1,1,1 };

//        RemoveDuplicates(vec);
//        Assert(is_permutation(vbeg, vend, begin(vector<int>{1})));
//    }
//}

//int main()
//{
//    TestRunner r;
//    r.RunTest(Test, "Test");
//    return 0;
//}