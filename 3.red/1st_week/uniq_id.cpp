#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define LOG(x) cout << #x << " = " << x << endl

#define CONCAT(x) var##x
#define ASSIST(x) CONCAT(x)
#define UNIQ_ID ASSIST(__LINE__)

int main() {
    string strin = "qwerqw";
    LOG(CONCAT(__LINE__));
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = { "hello", "world" };

    vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}
