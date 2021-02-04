#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <queue>

#include "test_runner.h"

template <typename T>
class PriorityCollection {
 private:
    using Priority   = int;
    using Position   = typename std::list<T>::iterator;
    using Collection = std::map<Priority, std::list<T>>;
    Collection collection_;

 public:
  using Id = typename std::pair<const Priority, Position>;

 public:
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
      auto& zero = collection_[0];
      zero.push_back(std::move(object));
      return {0, std::prev(zero.end())};
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
//   template <typename ObjInputIt, typename IdOutputIt>
//   void Add(ObjInputIt range_begin, ObjInputIt range_end,
//            IdOutputIt ids_begin) {
//   }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
      if (collection_.count(id.first)) {
          auto& cont = collection_.at(id.first);
          return (id.second != cont.end());
      }
      return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
        return *id.second;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      auto& lower_list  = collection_[id.first];
      auto& higher_list = collection_[id.first + 1];
      higher_list.splice(higher_list.end(), lower_list, id.second, std::next(id.second));
  }

  // Получить объект с максимальным приоритетом и его приоритет
  std::pair<const T&, int> GetMax() const {
    auto& last_pair = *std::prev(collection_.cend());
    const T& object = last_pair.second.back();
    return {object, last_pair.first};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
//   pair<T, int> PopMax();
};

class StringNonCopyable : public std::string {
 public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  std::cout << strings.IsValid(white_id) << "\n";

  strings.Promote(yellow_id);
  for (int i = 0; i < 3; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    ASSERT_EQUAL(strings.Get(red_id), "red");
    ASSERT_EQUAL(strings.Get(yellow_id), "yellow");
    ASSERT_EQUAL(strings.Get(white_id), "white");
  }
  {
    const auto& pair = strings.GetMax();
    ASSERT_EQUAL(pair.first, "red");
    ASSERT_EQUAL(pair.second, 2);
  }
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "red");
//     ASSERT_EQUAL(item.second, 2);
//   }
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "yellow");
//     ASSERT_EQUAL(item.second, 2);
//   }
//   {
//     const auto item = strings.PopMax();
//     ASSERT_EQUAL(item.first, "white");
//     ASSERT_EQUAL(item.second, 0);
//   }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
