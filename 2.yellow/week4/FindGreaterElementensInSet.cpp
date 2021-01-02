#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    return { find_if (begin(elements), end(elements),
                [&](const T& element)  { return element > border; }),
            end(elements)};
}
