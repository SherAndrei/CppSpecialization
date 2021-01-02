#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename It>
void PrintRange(It begin, It end) {
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    size_t size;
    cin >> size;

    vector<int> permut(size);
    for (size_t i = 1; i <= size; ++i)
        permut[i - 1] = size - i + 1;

    do {
        PrintRange(begin(permut), end(permut));
    } while (prev_permutation(begin(permut), end(permut)));

    return 0;
}
