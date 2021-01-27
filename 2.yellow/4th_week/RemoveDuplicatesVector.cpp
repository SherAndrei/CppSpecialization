#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements);

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    sort(begin(elements), end(elements));
    elements.erase(unique(begin(elements), end(elements)), end(elements));
}

/*
void Test()
{
   vector<int> vec;
   auto vbeg = begin(vec);
   auto vend = end(vec);
   {
       RemoveDuplicates(vec);
       AssertEqual(vec, vector<int>{});
   }
   {
       vec = {1,1};

       RemoveDuplicates(vec);
       Assert(is_permutation(vbeg, vend, begin(vector<int>{1})));
   }
   {
       vec = { 1,2,1 };

       RemoveDuplicates(vec);
       Assert(is_permutation(vbeg, vend, begin(vector<int>{1,2})));
   }
   {
       vec = { 1,1,2 };

       RemoveDuplicates(vec);
       Assert(is_permutation(vbeg, vend, begin(vector<int>{1, 2})));
   }
   {
       vec = { 1,1,1 };

       RemoveDuplicates(vec);
       Assert(is_permutation(vbeg, vend, begin(vector<int>{1})));
   }
}
*/
