#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

/*
2 PARTS

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it_beg = begin(elements);
    auto it_end = end(elements);
    auto it_mid = begin(elements) + elements.size() / 2;

    MergeSort(it_beg, it_mid);
    MergeSort(it_mid, it_end);

    merge(it_beg, it_mid, it_mid, it_end, range_begin);
}
*/

/*3 PARTS*/

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it_beg = begin(elements);
    auto it_end = end(elements);
    auto it_fir_th = begin(elements) + elements.size() / 3;
    auto it_sec_th = begin(elements) + 2 * elements.size() / 3;

    MergeSort(it_beg, it_fir_th);
    MergeSort(it_fir_th, it_sec_th);
    MergeSort(it_sec_th, it_end);

    vector<typename RandomIt::value_type> temp;
    merge(it_beg, it_fir_th, it_fir_th, it_sec_th, back_inserter(temp));
    merge(begin(temp), end(temp), it_sec_th, it_end, range_begin);
}
