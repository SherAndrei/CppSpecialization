#include <set>
#include <iostream>
using namespace std;


int main()
{
    size_t amount;
    cin >> amount;

    set<string> mySet;

    for (size_t i = 0; i < amount; i++)
    {
        string str;
        cin >> str;
       
        mySet.insert(str);
    }

    cout << mySet.size() << endl;

    return 0;
}

// 6 first second first third second second