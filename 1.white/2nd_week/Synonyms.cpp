#include <set>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

enum class Request {
    Unknown = 0,
    ADD,
    COUNT,
    CHECK
};

Request getRequest(const string& req) {
    if (!req.compare("ADD"))  return Request::ADD;
    if (!req.compare("COUNT")) return Request::COUNT;
    if (!req.compare("CHECK")) return Request::CHECK;

    return Request::Unknown;
}

int main() {
    size_t amount;
    cin >> amount;

    map<string, set<string>> wordToSynonyms;

    for (size_t i = 0; i < amount; i++) {
        string str;
        cin >> str;

        Request another = getRequest(str);

        switch (another) {
        case Request::Unknown: return -1;

        case Request::ADD: {
            string first, second;
            cin >> first >> second;

            wordToSynonyms[first].insert(second);
            wordToSynonyms[second].insert(first);


            first.clear();
            second.clear();
            break;
        }
        case Request::COUNT: {
            string word;
            cin >> word;

            cout << wordToSynonyms[word].size() << endl;

            word.clear();
            break;
        }
        case Request::CHECK: {
            string first, second;
            cin >> first >> second;

            (wordToSynonyms[first].count(second))
                ? cout << "YES" << endl
                : cout << "NO"  << endl;

            first.clear();
            second.clear();
            break;
        }
        default:
            break;
        }
        str.clear();
    }

    wordToSynonyms.clear();
    return 0;
}
