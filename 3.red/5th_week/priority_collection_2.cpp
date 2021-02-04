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

template <typename Iterator>
class IteratorRange {
 public:
    IteratorRange(Iterator begin, Iterator end)
        : _begin(begin), _end(end), _size(std::distance(begin, end)) {}

    void set_begin(Iterator begin) { _begin = begin; }
    void set_end(Iterator end)     { _end   = end; }

    Iterator begin()  const { return _begin; }
    Iterator end()    const { return _end; }
    size_t   size()   const { return _size; }
 private:
    Iterator _begin, _end;
    size_t _size;
};

template <typename T>
class PriorityCollection {
 private:
    using Priority   = int;
    using Position   = typename std::list<T>::iterator;
    using Collection = std::list<T>;
    Collection collection_;
    std::map<Priority, IteratorRange<Position>> priority_ranges;

 public:
  using Id = typename std::pair<Priority, Position>;

 public:
  PriorityCollection() {
      priority_ranges.emplace(0, IteratorRange(collection_.begin(), collection_.end()));
  }
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    auto res_iter = collection_.insert(priority_ranges.at(0).end(), std::move(object));
    priority_ranges.at(0) = {collection_.begin(), std::next(res_iter)};
    return {0, res_iter};
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
      return priority_ranges.count(id.first) && id.second != collection_.end();
  }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return *id.second;
    }

 private:
    template<typename Iterator>
    void shift(Iterator from, Iterator to) {
        collection_.splice(to, collection_, from);
    }

 public:
    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        // если такой приоритет + 1 уже есть, то
        // вставляем в конец рэнжа
        auto& [current_priority, object_position] = id;
        const auto& [lower, upper] = priority_ranges.equal_range(current_priority);
        if (lower == priority_ranges.end() &&
            upper == priority_ranges.end()) {
            shift(object_position, collection_.end());
            priority_ranges.emplace(current_priority + 1,
                                    IteratorRange(std::prev(collection_.end()), collection_.end()));
        } else if (lower != priority_ranges.end() &&
                   upper == priority_ranges.end()) {
            IteratorRange<Position>& current_range = lower->second;
            if (current_range.size() == 1) {
                priority_ranges.erase(current_priority);
            }
            shift(object_position, collection_.end());
            priority_ranges.emplace(current_priority + 1,
                    IteratorRange(std::prev(collection_.end()), collection_.end()));
        }



        // если приоритета не было, то
        // находим ближайший правый элемент к этому приоритету
        // если его нет, вставляем в конец списка
        // если есть делаем сплайс
    }

    // Получить объект с максимальным приоритетом и его приоритет
    std::pair<const T&, int> GetMax() const {
        const auto& pair = std::prev(priority_ranges.end());
        const IteratorRange<Position>& max_prior_range = pair->second;
        const T& last_max_prior_elem = *(std::prev(max_prior_range.end()));
        return {last_max_prior_elem, pair->first};
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

void TestAdd() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    ASSERT_EQUAL(strings.Get(red_id), "red");
    ASSERT_EQUAL(strings.Get(yellow_id), "yellow");
    ASSERT_EQUAL(strings.Get(white_id), "white");
}


void TestPromote() {
    PriorityCollection<StringNonCopyable> strings;

    const auto white_id = strings.Add("white");

    const auto& pair_1 = strings.GetMax();
    ASSERT_EQUAL(pair_1.first, "white");
    ASSERT_EQUAL(pair_1.second, 0);

    strings.Promote(white_id);

    const auto& pair_2 = strings.GetMax();
    ASSERT_EQUAL(pair_2.first, "white");
    ASSERT_EQUAL(pair_2.second, 1);

    strings.Promote(white_id);

    const auto& pair_3 = strings.GetMax();
    ASSERT_EQUAL(pair_3.first, "white");
    ASSERT_EQUAL(pair_3.second, 2);
}

void TestNoCopy() {
//   PriorityCollection<StringNonCopyable> strings;
//   const auto white_id = strings.Add("white");
//   const auto yellow_id = strings.Add("yellow");
//   const auto red_id = strings.Add("red");

//   strings.Promote(yellow_id);
//   for (int i = 0; i < 3; ++i) {
//     strings.Promote(red_id);
//   }
//   strings.Promote(yellow_id);
//   {
//     const auto& pair = strings.GetMax();
//     ASSERT_EQUAL(pair.first, "red");
//     ASSERT_EQUAL(pair.second, 2);
//   }
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
  RUN_TEST(tr, TestAdd);
  RUN_TEST(tr, TestPromote);
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
