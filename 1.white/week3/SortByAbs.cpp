#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int amount;
    cin >> amount;

    vector<int> vecNum(amount);
    string s;
    s += "Hello"; {
        s += " world";
    }
    cout << s;
    for (int& item : vecNum)
        cin >> item;

    sort(vecNum.begin(), vecNum.end(), [](int x, int y) { return abs(x) < abs(y); });

    for (const auto& item : vecNum)
        cout << item << " ";

    return 0;
}
