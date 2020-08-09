#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt");
    int result, strings, columns;

    if (input)
    {
        input >> strings >> columns;

        for (int i = 0; i < strings * columns; ++i)
        {
            input >> result;
            input.ignore(1);

            if (i != 0 && i != strings * columns && i % columns == 0)
                cout << endl;

           if(i % columns != 0)
            cout << " ";
            
            cout << setw(10) << result;
        }
    }

    return 0;
}