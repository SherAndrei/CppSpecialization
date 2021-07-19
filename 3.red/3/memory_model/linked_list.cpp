#include <deque>
#include <vector>

#include "test_runner.h"

using namespace std;

template <typename T>
class LinkedList {
 public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    ~LinkedList() {
        while (_head)
            PopFront();
    }

    void PushFront(const T& value) {
        Node* new_head = new Node{ value, _head };
        _head = new_head;
    }

    void InsertAfter(Node* node, const T& value) {
        if (node) {
            Node* new_node = new Node{ value, node->next };
            node->next = new_node;
        } else {
            PushFront(value);
        }
    }
    void RemoveAfter(Node* node) {
        if (!node) {
            PopFront();
        } else if (node->next) {
            Node* target = node->next;
            node->next = target->next;
            delete target;
        }
    }
    void PopFront() {
        if (!_head)
            return;
        Node* new_head = _head->next;
        delete _head;
        _head = new_head;
    }
    Node* GetHead()             { return _head; }
    const Node* GetHead() const { return _head; }

 private:
  Node*  _head   = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
    {
        LinkedList<int> list;

        list.PushFront(1);
        ASSERT_EQUAL(list.GetHead()->value, 1);
        list.PushFront(2);
        ASSERT_EQUAL(list.GetHead()->value, 2);
        list.PushFront(3);
        ASSERT_EQUAL(list.GetHead()->value, 3);

        const vector<int> expected = { 3, 2, 1 };

        ASSERT_EQUAL(ToVector(list), expected);
    }
    {
        LinkedList<string> list;
        for (int i = 0; i < 5; i++)
            list.PushFront(to_string(i));

        vector<string> expected;
        for (int i = 4; i >= 0; i--)
            expected.push_back(to_string(i));
        ASSERT_EQUAL(ToVector(list), expected);
    }
    {
        LinkedList<int> l;
        l.PushFront(1);
        l.RemoveAfter(l.GetHead());
        ASSERT_EQUAL(ToVector(l), (vector<int>{1}));
    }
}

void TestInsertAfter() {
    {
        LinkedList<string> list;

        list.PushFront("a");
        auto head = list.GetHead();
        ASSERT(head);
        ASSERT_EQUAL(head->value, "a");

        list.InsertAfter(head, "b");
        const vector<string> expected1 = { "a", "b" };

        ASSERT_EQUAL(ToVector(list), expected1);

        list.InsertAfter(head, "c");
        const vector<string> expected2 = { "a", "c", "b" };

        ASSERT_EQUAL(ToVector(list), expected2);
    }
    {
        LinkedList<int> l;
        l.InsertAfter(nullptr, 1);
        ASSERT_EQUAL(l.GetHead()->value, 1);
        ASSERT(l.GetHead()->next == nullptr);
        l.InsertAfter(l.GetHead(), 2);
        ASSERT_EQUAL(l.GetHead()->next->value, 2);
        ASSERT(l.GetHead()->next->next == nullptr);
    }
}

void TestRemoveAfter() {
    {
        LinkedList<int> list;
        for (int i = 1; i <= 5; ++i) {
            list.PushFront(i);
        }

        const vector<int> expected = { 5, 4, 3, 2, 1 };

        ASSERT_EQUAL(ToVector(list), expected);

        auto next_to_head = list.GetHead()->next;
        list.RemoveAfter(next_to_head);  // удаляем 3
        list.RemoveAfter(next_to_head);  // удаляем 2

        const vector<int> expected1 = { 5, 4, 1 };

        ASSERT_EQUAL(ToVector(list), expected1);

        while (list.GetHead()->next) {
            list.RemoveAfter(list.GetHead());
        }
        ASSERT_EQUAL(list.GetHead()->value, 5);
    }
    {
        LinkedList<int> l;
        l.RemoveAfter(nullptr);
        ASSERT(l.GetHead() == nullptr);

        for (int i = 0; i < 4; ++i)
            l.PushFront(i);
        l.RemoveAfter(l.GetHead()->next->next);
        ASSERT_EQUAL(ToVector(l), (vector<int>{3, 2, 1}));

        l.RemoveAfter(l.GetHead());
        ASSERT_EQUAL(ToVector(l), (vector<int>{3, 1}));

        l.RemoveAfter(nullptr);
        ASSERT_EQUAL(ToVector(l), (vector<int>{1}));

        l.RemoveAfter(l.GetHead()->next);
        ASSERT_EQUAL(ToVector(l), (vector<int>{}));
        ASSERT(l.GetHead() == nullptr);
        // ASSERT_EQUAL(l, nullptr);
    }
}
void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}
