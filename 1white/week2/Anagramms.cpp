#include <map>
#include <iostream>
using namespace std;

map<char, int> BuildCharCounter(const string& str)
{
    map<char, int> counter;

    for (const char& ch : str)
    {
        ++counter[ch];
    }

    return counter;
}

void printMap(const map<char, int>& map)
{
    for (const auto& item : map)
    {
        cout << item.first << ": " << item.second << endl;
    }
}


bool compareMaps(const map<char, int>& first, const map<char, int>& second)
{
    return first == second;
}


int main()
{
    size_t amount;
    cin >> amount;


    for (size_t i = 0; i < amount; ++i)
    {
        string first, second;
        cin >> first >> second;

        (compareMaps(BuildCharCounter(first), BuildCharCounter(second)))
            ? cout << "YES" << endl
            : cout << "NO"  << endl;

        first.clear();
        second.clear();
    }


    return 0;
}

// 2 abab abba aaab aabb
      
