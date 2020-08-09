
/*ƒва слова называютс€ синонимами друг друга, 
если они имеют похожие значени€. –еализуйте 
следующие операции над словарЄм синонимов:

ADD word1 word2 Ч добавить в словарь пару синонимов (word1, word2).
COUNT word Ч узнать количество синонимов слова word.
CHECK word1 word2 Ч проверить, €вл€ютс€ ли слова word1 и word2 синонимами.
—лова word1 и word2 считаютс€ синонимами, если среди запросов ADD был хот€
бы один запрос ADD word1 word2 или ADD word2 word1.*/

#include <set>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

enum class Request
{
    Unknown = 0,
    ADD,
    COUNT,
    CHECK
};

Request getRequest(const string& req)
{
    if (!req.compare("ADD"))  return Request::ADD;
    if (!req.compare("COUNT")) return Request::COUNT;
    if (!req.compare("CHECK")) return Request::CHECK;

    return Request::Unknown;
}

int main()
{
    size_t amount;
    cin >> amount;

    map<string, set<string>> wordToSynonyms;

    for (size_t i = 0; i < amount; i++)
    {
        string str;
        cin >> str;

        Request another = getRequest(str);

        switch (another)
        {
        case Request::Unknown: return -1;

        case Request::ADD:
        {
            string first, second;
            cin >> first >> second;

            wordToSynonyms[first].insert(second);
            wordToSynonyms[second].insert(first);


            first.clear();
            second.clear();
            break;
        }
        case Request::COUNT:
        {
            string word;
            cin >> word;

            cout << wordToSynonyms[word].size() << endl;

            word.clear();
            break;
        }
        case Request::CHECK:
        {
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

//8 ADD program code COUNT cipher ADD code cipher COUNT code COUNT program CHECK code program CHECK program cipher CHECK cpp java
