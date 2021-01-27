#include <iostream>
#include <vector>
#define BASE 2

using namespace std;

int main() {
    int Numb;
    vector<int> newNumb;

    cin >> Numb;

    if (Numb == 0)
        newNumb.push_back(Numb);

    while (Numb != 0) {
        newNumb.push_back(Numb % BASE);
        Numb /= BASE;
    }

    for (int i = newNumb.size()-1; i >= 0; --i) {
        cout << newNumb[i];
    }

    return 0;
}

