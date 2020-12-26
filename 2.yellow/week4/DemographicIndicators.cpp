#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

//enum class Gender {
//    FEMALE,
//    MALE
//};

//
//struct Person
//{
//    int age;  // �������
//    Gender gender;  // ���
//    bool is_employed;  // ����� �� ������
//};

//
//template <typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
//    if (range_begin == range_end) {
//        return 0;
//    }
//    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//    auto middle = begin(range_copy) + range_copy.size() / 2;
//    nth_element(
//        begin(range_copy), middle, end(range_copy),
//        [](const Person& lhs, const Person& rhs) {
//            return lhs.age < rhs.age;
//        }
//    );
//    return middle->age;
//}

template<typename It>
void PrintRange (It begin, It end) {
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}

void PrintStats(vector<Person> persons) {
        cout << "Median age = " <<ComputeMedianAge(begin(persons), end(persons)) << endl; {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::FEMALE; });
        cout << "Median age for females = " << ComputeMedianAge(begin(persons), it) << endl;
    } {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::MALE; });
        cout << "Median age for males = " <<ComputeMedianAge(begin(persons), it) << endl;
    } {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::FEMALE && person.is_employed == true; });
        cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), it) << endl;
    } {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::FEMALE && person.is_employed == false; });
        cout << "Median age for unemployed females = " << ComputeMedianAge(begin(persons), it) << endl;
    } {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::MALE && person.is_employed == true; });
        cout << "Median age for employed males = " << ComputeMedianAge(begin(persons), it) << endl;
    } {
        auto it = partition(begin(persons), end(persons),
            [](const Person& person) { return person.gender == Gender::MALE && person.is_employed == false; });
        cout << "Median age for unemployed males = " << ComputeMedianAge(begin(persons), it) << endl;
    }

}

//void PrintStats(vector<Person> persons) {
//    // ����������� ������� ����� � ����������:
//    //                  persons
//    //                 /      \
//    //          females        males
//    //         /       \     /      \
//    //      empl.  unempl. empl.   unempl.
//    auto females_end = partition(
//        begin(persons), end(persons), [](const Person& p) {
//            return p.gender == Gender::FEMALE;
//        }
//    );
//    auto employed_females_end = partition(
//        begin(persons), females_end, [](const Person& p) {
//            return p.is_employed;
//        }
//    );
//    auto employed_males_end = partition(
//        females_end, end(persons), [](const Person& p) {
//            return p.is_employed;
//        }
//    );
//
//    // ������ ������������ ��� ������ ��������� � ������� ����������
//    cout << "Median age = "
//        << ComputeMedianAge(begin(persons), end(persons)) << endl;
//    cout << "Median age for females = "
//        << ComputeMedianAge(begin(persons), females_end) << endl;
//    cout << "Median age for males = "
//        << ComputeMedianAge(females_end, end(persons)) << endl;
//    cout << "Median age for employed females = "
//        << ComputeMedianAge(begin(persons), employed_females_end) << endl;
//    cout << "Median age for unemployed females = "
//        << ComputeMedianAge(employed_females_end, females_end) << endl;
//    cout << "Median age for employed males = "
//        << ComputeMedianAge(females_end, employed_males_end) << endl;
//    cout << "Median age for unemployed males = "
//        << ComputeMedianAge(employed_males_end, end(persons)) << endl;
//}