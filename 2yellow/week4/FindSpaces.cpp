#include <iostream>
#include <vector>   
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename It>
void PrintRange (It begin, It end)
{
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}

int main()
{
    string s("abc def ght klm");
    for    (auto it = find(begin(s), end(s), ' ');
            it != end(s); 
            it = find(next(it), end(s), ' '))
        cout << distance(begin(s),it) << endl;
       
}
