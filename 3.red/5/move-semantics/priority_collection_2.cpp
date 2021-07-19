#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "test_runner.h"

template <typename T>
class PriorityCollection {
 public:
    struct Element {
        T obj;
        int priority = 0;
        size_t pos  = 0;
        Element(T&& new_obj, int new_priority, size_t new_pos)
            : obj(std::move(new_obj)), priority(new_priority), pos(new_pos) {}
        Element(const Element& other) = delete;
        Element(Element&& other) = default;
        Element& operator=(const Element&) = delete;
        Element& operator=(Element&&) = default;

        bool operator==(const Element& other) const
            { return obj == other.obj; }
        bool operator!=(const Element& other) const
            { return obj != other.obj; }
        bool operator<(const Element& other) const
            { return std::tie(priority, pos) < std::tie(other.priority, other.pos); }
    };
    using Id = typename std::multiset<Element>::const_iterator;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        Element elem{std::move(object), 0, _elements.size()};
        return _elements.emplace(std::move(elem));
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
            IdOutputIt ids_begin) {
        while (range_begin != range_end) {
            *ids_begin++ = Add(std::move(*range_begin++));
        }
    }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        if (id == _elements.end())
            return false;
        return _elements.find(*id) != _elements.end();
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const
        { return id->obj; }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        auto handle = _elements.extract(id);
        handle.value().priority++;
        _elements.insert(std::move(handle));
    }

    // Получить объект с максимальным приоритетом и его приоритет
    std::pair<const T&, int> GetMax() const {
        auto last_elem_it = std::prev(_elements.end());
        return { last_elem_it->obj, last_elem_it->priority };
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    std::pair<T, int> PopMax() {
        auto max_pos = std::prev(_elements.end());
        auto handle = _elements.extract(max_pos);
        auto pair = std::make_pair(std::move(handle.value().obj), handle.value().priority);
        return pair;
    }

 private:
    std::multiset<Element> _elements;
};


class StringNonCopyable : public std::string {
 public:
    using std::string::string;  // Позволяет использовать конструкторы строки
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

  ASSERT_EQUAL(strings.Get(red_id), "red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto& item_ref = strings.GetMax();
    ASSERT_EQUAL(item_ref.first, "yellow");
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestAddIters() {
    {
        std::vector<StringNonCopyable> strings;
        strings.push_back("apple");
        strings.push_back("orange");
        std::vector<PriorityCollection<StringNonCopyable>::Id> ids{strings.size()};
        PriorityCollection<StringNonCopyable> collection;
        collection.Add(strings.begin(), strings.end(), ids.begin());
        ASSERT_EQUAL(collection.Get(ids.back()), "orange");
        ASSERT_EQUAL(collection.Get(ids.front()), "apple");
    }
}

void TestIsValid() {
    {
        PriorityCollection<StringNonCopyable> strings;

        const auto yellow_id = strings.Add("yellow");
        ASSERT(strings.IsValid(yellow_id));

        strings.Promote(yellow_id);
        ASSERT(strings.IsValid(yellow_id));
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestAddIters);
  RUN_TEST(tr, TestIsValid);
  return 0;
}

/*
template <typename T>
class PriorityCollection {
public:
  using Id = int;

  Id Add(T object) {
    const Id new_id = objects.size();
    objects.push_back({move(object)});
    sorted_objects.insert({0, new_id});
    return new_id;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    while (range_begin != range_end) {
      *ids_begin++ = Add(move(*range_begin++));
    }
  }

  bool IsValid(Id id) const {
    return id >= 0 && id < objects.size() &&
        objects[id].priority != NONE_PRIORITY;
  }

  const T& Get(Id id) const {
    return objects[id].data;
  }

  void Promote(Id id) {
    auto& item = objects[id];
    const int old_priority = item.priority;
    const int new_priority = ++item.priority;
    sorted_objects.erase({old_priority, id});
    sorted_objects.insert({new_priority, id});
  }

  pair<const T&, int> GetMax() const {
    const auto& item = objects[prev(sorted_objects.end())->second];
    return {item.data, item.priority};
  }

  pair<T, int> PopMax() {
    const auto sorted_objects_it = prev(sorted_objects.end());
    auto& item = objects[sorted_objects_it->second];
    sorted_objects.erase(sorted_objects_it);
    const int priority = item.priority;
    item.priority = NONE_PRIORITY;
    return {move(item.data), priority};
  }

private:
  struct ObjectItem {
    T data;
    int priority = 0;
  };
  static const int NONE_PRIORITY = -1;

  vector<ObjectItem> objects;
  set<pair<int, Id>> sorted_objects;
};
*/
