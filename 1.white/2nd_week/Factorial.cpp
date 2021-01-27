#include <iostream>

using namespace std;

int Factorial(int number) {
    return (number > 1) ? number * Factorial(number - 1) : 1;
}

int main() {
    int number;
    cin >> number;

    cout << Factorial(number);

    return 0;
}

