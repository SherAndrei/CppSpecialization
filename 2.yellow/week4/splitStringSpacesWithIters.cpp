#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto itBeg = begin(s), itEnd = end(s);
    while (itBeg != end(s)) {
        itEnd = find(itBeg, end(s), ' ');
        result.push_back({ itBeg, find(itBeg, end(s), ' ') });
        if (itEnd != end(s))
            itBeg = ++itEnd;
        else
            break;
    }
    return result;
}

/*
vector<string> SplitIntoWords(const string& str) {
    vector<string> result;

    auto str_begin = begin(str);
    const auto str_end = end(str);

    while (true) {
        auto it = find(str_begin, str_end, ' ');
        result.push_back(string(str_begin, it));
        if (it == str_end) break;
        else str_begin = it + 1;
    }
    return result;
}
*/
