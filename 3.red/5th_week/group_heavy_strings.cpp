#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <set>

#include "test_runner.h"

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = std::vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

class NonRepetativeString {
 public:
    NonRepetativeString() = default;

    explicit NonRepetativeString(std::string_view strv) {
        for (const auto& letter : strv) {
            size_t pos = data_.find(letter);
            if (pos == std::string::npos) {
                data_.push_back(letter);
            }
        }
    }

    std::string& str() {
        return data_;
    }

 private:
    std::string data_;
};


template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) {
    std::vector<Group<String>> groups;
    std::map<size_t, NonRepetativeString> pos_to_strings;
    bool is_in_group = false;
    int group_num = -1;

    for (auto& string : strings) {
        is_in_group = false;
        for (size_t i = 0u; i < groups.size(); i++) {
            NonRepetativeString& group_str = pos_to_strings.at(i);
            // ищем слово в группе
            if (group_str.str().find_first_not_of(string) == std::string::npos &&
                string.find_first_not_of(group_str.str()) == std::string::npos) {
                is_in_group = true;
                group_num = i;
                break;
            } else {
                is_in_group = false;
            }
        }

        if (is_in_group) {
            groups[group_num].push_back(std::move(string));
        } else {
            size_t new_group_pos = groups.size();
            pos_to_strings[new_group_pos] = NonRepetativeString(string);
            groups.push_back({std::move(string)});
        }
    }

    return groups;
}


using namespace std;

void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}
