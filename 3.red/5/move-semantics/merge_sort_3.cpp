#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;
    vector<typename RandomIt::value_type> elements(
        make_move_iterator(range_begin),
        make_move_iterator(range_end));
    auto it_beg    = begin(elements);
    auto it_fir_th = begin(elements) + elements.size() / 3;
    auto it_sec_th = begin(elements) + 2 * elements.size() / 3;
    auto it_end    = end(elements);

    MergeSort(it_beg, it_fir_th);
    MergeSort(it_fir_th, it_sec_th);
    MergeSort(it_sec_th, it_end);

    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(it_beg), make_move_iterator(it_fir_th),
          make_move_iterator(it_fir_th), make_move_iterator(it_sec_th),
          back_inserter(temp));
    merge(make_move_iterator(begin(temp)), make_move_iterator(end(temp)),
          make_move_iterator(it_sec_th), make_move_iterator(it_end),
          range_begin);
}


class Tracker {
 public:
    Tracker() {
        std::cout << "Default ctor\n";
    }
    Tracker(const Tracker&) {
        std::cout << "Copy ctor\n";
    }
    Tracker(Tracker&&) {
        std::cout << "Move ctor\n";
    }
    Tracker& operator=(const Tracker&) {
        std::cout << "Copy ass\n";
        return *this;
    }
    Tracker& operator=(Tracker&&) {
        std::cout << "Move ass\n";
        return *this;
    }

    bool operator<(const Tracker&) const {
        return true;
    }
};

void TestTracker() {
    vector<Tracker> trackers(9);
    MergeSort(begin(trackers), end(trackers));
    // ASSERT(is_sorted(begin(trackers), end(trackers)));
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 5, 1, 3, 8, 9, 2, 7};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTracker);
  RUN_TEST(tr, TestIntVector);
  return 0;
}

/*
In file included from /usr/include/c++/7/bits/stl_tempbuf.h:60:0,\n
from /usr/include/c++/7/bits/stl_algo.h:62,\n
from /usr/include/c++/7/algorithm:62,\n
from /tmp/submissioniy64lul9/merge_sort_3.cpp:1:\n
/usr/include/c++/7/bits/stl_construct.h: In instantiation of 'void std::_Construct(_T1*, _Args&& ...) [with _T1 = __CourseraMoveTracker; _Args = {__CourseraMoveTracker&}]':\n

/usr/include/c++/7/bits/stl_uninitialized.h:83:18:   required from 'static _ForwardIterator std::__uninitialized_copy<_TrivialValueTypes>::__uninit_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; _ForwardIterator = __CourseraMoveTracker*; bool _TrivialValueTypes = false]'\n
/usr/include/c++/7/bits/stl_uninitialized.h:134:15:   required from '_ForwardIterator std::uninitialized_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; _ForwardIterator = __CourseraMoveTracker*]'\n
/usr/include/c++/7/bits/stl_uninitialized.h:289:37:   required from '_ForwardIterator std::__uninitialized_copy_a(_InputIterator, _InputIterator, _ForwardIterator, std::allocator<_Tp>&) [with _InputIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; _ForwardIterator = __CourseraMoveTracker*; _Tp = __CourseraMoveTracker]'\n
/usr/include/c++/7/bits/stl_vector.h:1326:33:   required from 'void std::vector<_Tp, _Alloc>::_M_range_initialize(_ForwardIterator, _ForwardIterator, std::forward_iterator_tag) [with _ForwardIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; _Tp = __CourseraMoveTracker; _Alloc = std::allocator<__CourseraMoveTracker>]'\n
/usr/include/c++/7/bits/stl_vector.h:1299:23:   required from 'void std::vector<_Tp, _Alloc>::_M_initialize_dispatch(_InputIterator, _InputIterator, std::__false_type) [with _InputIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; _Tp = __CourseraMoveTracker; _Alloc = std::allocator<__CourseraMoveTracker>]'\n
/usr/include/c++/7/bits/stl_vector.h:414:26:   required from 'std::vector<_Tp, _Alloc>::vector(_InputIterator, _InputIterator, const allocator_type&) [with _InputIterator = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >; <template-parameter-2-2> = void; _Tp = __CourseraMoveTracker; _Alloc = std::allocator<__CourseraMoveTracker>; std::vector<_Tp, _Alloc>::allocator_type = std::allocator<__CourseraMoveTracker>]'\n
/tmp/submissioniy64lul9/merge_sort_3.cpp:79:46:   required from 'void MergeSort(RandomIt, RandomIt) [with RandomIt = __gnu_cxx::__normal_iterator<__CourseraMoveTracker*, std::vector<__CourseraMoveTracker> >]'\n
/tmp/submissioniy64lul9/merge_sort_3.cpp:177:41:   required from here\n
/usr/include/c++/7/bits/stl_construct.h:75:7: error: use of deleted function '__CourseraMoveTracker::__CourseraMoveTracker(const __CourseraMoveTracker&)'\n
     { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }\n
       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n
compilation terminated due to -Wfatal-errors.\n
"
*/