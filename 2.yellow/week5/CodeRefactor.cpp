#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
 public:
    Person(const string& name, const string& activity)
        : _name(name)
        , _activity(activity) {}


    ostream& Do(const string& action) const {
        return cout << _activity << ": " << _name << " " << action;
    }

    virtual void Walk(const string& destination) const {
        Do("walks to ") << destination << endl;
    }


    string Name()     const { return _name; }
    string Activity() const { return _activity; }

 protected:
    const string _name;
    const string _activity;
};


class Student : public Person {
 public:

    Student(const string& name, const string& favouriteSong)
        : Person(name, "Student")
        , FavouriteSong(favouriteSong) {}

    void Learn() const {
        Do("learns");
    }

    void Walk(const string& destination) const override {
        Do("walks to ") << destination << endl;
        SingSong();
    }

    void SingSong() const {
        Do("sings a song: ") << FavouriteSong << endl;
    }

 public:
    const string FavouriteSong;
};



class Teacher : public Person {
 public:

    Teacher(const string& name, const string& subject)
        : Person(name, "Teacher")
        , Subject(subject) {}

    void Teach() const {
        Do("teaches: ") << Subject << endl;
    }

 private:
    const string Subject;
};



class Policeman : public Person {
 public:
    Policeman(const string& name)
        : Person(name, "Policeman") {}

    void Check(const Person& pers) const {
        Do("checks ") << pers.Activity() << ". " << pers.Activity() << "'s name is: " << pers.Name() << endl;
    }
};


void VisitPlaces(const Person& pers, const vector<string>& places) {
    for (const auto& p : places) {
        pers.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}