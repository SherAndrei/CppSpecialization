#include <string>

using namespace std;

struct Specialization {
    string value;
    explicit Specialization(const string& new_value) {
        value = new_value;
    }
};


struct Course {
    string value;
    explicit Course(const string& new_value) {
        value = new_value;
    }
};


struct Week {
    string value;
    explicit Week(const string& new_value) {
        value = new_value;
    }
};


struct LectureTitle {
    string specialization;
    string course;
    string week;

    LectureTitle(Specialization new_Specialization, Course new_course, Week new_week) {
        specialization =  new_Specialization.value;
        course = new_course.value;
        week = new_week.value;
    }
};
