#include <iostream>

using namespace std;

int Factorial(int number)
{
    if (number <= 1)
        return 1;
    else
        return number * Factorial(number - 1);
}

int main()
{
    int number;
    cin >> number;

    cout << Factorial(number);

    return 0;
}

