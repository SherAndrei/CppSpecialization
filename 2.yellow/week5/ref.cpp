#include <iostream>
#include <string>
#include <vector>

using namespace std;

class People {
 public:
    People(const string& name_, const string& occupation_) : Name(name_), class_type(occupation_){}

    virtual void DoAction(const string& act) {
        cout << class_type << ": " << Name << act << endl;
    }
    virtual void Walk(const string& dest) {
        DoAction(" walks to: " + dest);
    }

    const string class_type;
    const string Name;
};


class Student : public People {
 public:

    Student(const string& name, const string& favouriteSong) : People(name, "Student"),
    FavouriteSong(favouriteSong){}

    void Learn() {
        DoAction("learns");
    }

    virtual void Walk(const string& destination) override {
        DoAction(" walks to " + destination);
        DoAction(" sings a song: " + FavouriteSong);
    }

 private:
    const string FavouriteSong;
};



class Teacher : public People {
 public:

    Teacher(string name, string subject) : People(name, "Teacher"),
        Subject(subject) {}

    void Teach() {
        DoAction("teaches: " + Subject);
    }

 private:
    string Subject;
};



class Policeman : public People {
 public:
    Policeman(string name) : People(name, "Policeman") {}

    template <typename T>
    void Check(T subject) {
        DoAction(" checks " + subject.class_type + ". " + subject.class_type + "'s name is: " + subject.Name);
    }
};


template <typename T>
void VisitPlaces(T t_, vector<string> places) {
    for (auto p : places) {
        t_.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    int a;
    p.Check(a);
    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
