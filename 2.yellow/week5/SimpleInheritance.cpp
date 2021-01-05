#include <iostream>
#include <string>

using namespace std;

class Animal {
 public:
    explicit Animal(const string& str)
        : Name(str) {}

    const string Name;
};

class Dog : public Animal {
 public:
    explicit Dog(const string& str)
        : Animal(str) {}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
    Dog d("Barbos");
    d.Bark();
    return 0;
}
