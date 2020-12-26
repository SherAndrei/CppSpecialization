#include <iostream>

using namespace std;

int GCD(int first, int second) {
    while (first != 0 && second != 0) {
        if (first > second)
            first = first % second;
        else
            second = second % first;
    }

    return first + second;
}

int main() {
    int first, second;

    cin >> first >> second;

    cout << GCD(first, second);

    return 0;
}

