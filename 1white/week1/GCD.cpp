#include <iostream>

using namespace std;

/*
    В цикле в переменную first или second записывается остаток от деления. 
    Цикл завершается, когда хотя бы одна из переменных равна нулю. 
    Это значит, что другая содержит НОД. 
    Однако какая именно, мы не знаем. 
    Поэтому для НОД находим сумму этих переменных. 
    Поскольку в одной из переменных ноль, он не оказывает влияние на результат.
*/

int GCD(int first, int second)
{
    while (first != 0 && second != 0)
    {
        if (first > second)
            first = first % second;
        else
            second = second % first;
    }

    return first + second;
}

int main()
{
    int first, second;

    cin >> first >> second;

    cout << GCD(first, second);

    return 0;
}

