#include <iostream>
#include <list>
#include <algorithm>
#include "test_runner.h"

using namespace std;

// amount 100'000

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int amount;
    cin >> amount;

    list<int> athlets;
    vector<list<int>::iterator> position(100'000 + 1, athlets.end());
    for (int i = 0; i < amount; ++i) {
        int current, next;
        cin >> current >> next;
        position[current] = athlets.insert(position[next], current);
    }

    for (const auto& s : athlets) {
        cout << s << '\n';
    }
}
