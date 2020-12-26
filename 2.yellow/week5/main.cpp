#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
 public:
    Human(const string& name, const string& position)
        : Name(name), Position(position) {}

    virtual void Walk(const string& destination) const {
        DoTask(" walks to: ", destination);
        cout << endl;
    }

    const string GetName() const {
        return Name;
    }

    const string GetPos() const {
        return Position;
    }

    void DoTask(const string& action, const string& argument) const {
        cout << Position << ": " << Name << action << argument;
    }

 private:
    const string Name;
    // должность человека
    const string Position;
};



class Student : public Human {
 public:
    Student(const string& name, const string& favouriteSong)
            : Human(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        DoTask(" learns", "");
        cout << endl;
    }

    void SingSong() const {
        DoTask(" sings a song: ", FavouriteSong);
        cout << endl;
    }

    void Walk(const string& destination) const {
        DoTask(" walks to: ", destination);
        cout << endl;
        SingSong();
    }

 private:
    const string FavouriteSong;
};



class Teacher : public Human {
 public:
    Teacher(const string& name, const string& subject)
            : Human(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        DoTask(" teaches ", Subject);
        cout << endl;
    }

 private:
    const string Subject;
};



class Policeman : public Human {
 public:
    Policeman(const string& name) : Human(name, "Policeman") {}

    void Check(const Human& human) const {
        DoTask(" checks ", human.GetPos());
        cout << ". " << human.GetPos() << "'s name is: "
             << human.GetName() << endl;
    }
};



void VisitPlaces(const Human& pol, const vector<string>& places) {
    for (const string& p : places)
        pol.Walk(p);
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}