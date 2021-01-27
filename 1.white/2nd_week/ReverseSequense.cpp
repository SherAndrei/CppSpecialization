#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int>& vec) {
    for (size_t i = 0; i < vec.size()/2; ++i) {
        int tmp = vec[vec.size() - i - 1];
        vec[vec.size() - i - 1] = vec[i];
        vec[i] = tmp;
    }
}


int main() {
    vector<int> vec;
    for (int i = 0; i < 5; i++) {
        cin >> i;
        vec.push_back(i);
    }

    Reverse(vec);
    for (auto i : vec) {
        cout << i << " ";
    }
    return 0;
}

