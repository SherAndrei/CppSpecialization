#include <iostream>
#include <string>

using namespace std;

class ReversibleString {
 public:
    explicit ReversibleString(const string& another = string{} ) {
        myString = another;
    }

    void Reverse() {
        // reverse(begin(myString), end(myString));
        for (size_t i = 0; i < myString.size()/2; i++) {
            char temp = myString[i];
            myString[i] = myString[myString.size() - i - 1];
            myString[myString.size() - i - 1] = temp;
        }
    }

    string ToString() const { return myString; }

 private:
    string myString;
};

